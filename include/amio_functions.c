/* amio_functions.c defines the implementations of the
   wrapper functions which hide
   complexities of allegro. This is done so that many of the complexities
   of C are hidden from the beginner.

   Author: Cameron Harwood, School of Physics, Engineering and Technology
   University of York, Nov 2022.

   Notes:
   Two lists are used, following conventions provided in the Algorithms and Numerical Methods module lead by Dr. Stuart Porter.

   AudioSampleList - A doubly linked list, in which nodes contain a name for the sample and a pointer to an ALLEGRO_SAMPLE

   AudioInstanceList - A doubly linked list, in which nodes contain information about the current sample instance.

   The user assigns a name to each sample that is loaded. Each sample must have a unique name.

   A sample can have multiple instances at the same time.

   An instance is created based on the sample name.

   The user is able to define the volume, and instance type (Loop or play once).
*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<amio.h>

// AUDIO STATES
#define START    0
#define PLAYING  1

// STRUCTS
struct AudioInstanceNode
{
    uint8_t state;
    uint8_t type;
    float volume;

    ALLEGRO_SAMPLE_INSTANCE *sampleInstance;

    struct AudioInstanceNode* next;
    struct AudioInstanceNode* prev;
};

struct AudioInstanceList
{
    // A running count of the number of nodes in the list.
    int size;
    int capacity;

    // The addresses of the first and last nodes in the list.
    struct AudioInstanceNode* head;
    struct AudioInstanceNode* tail;
};

struct AudioSampleNode {
    // The name associated with this sample.
    char sampleName[MAX_AUDIO_SAMPLE_NAME_LENGTH];

    // The address of the allegro sample.
    ALLEGRO_SAMPLE* sample;

    // The addresses of the next and previous nodes.
    struct AudioSampleNode* next;
    struct AudioSampleNode* prev;
};


struct AudioSampleList {
    // A running count of the number of nodes in the list.
    int size;
    int capacity;

    // The addresses of the first and last nodes in the list.
    struct AudioSampleNode* head;
    struct AudioSampleNode* tail;
};

// AUDIO SAMPLE LIST FUNCTIONS

// Create a new node suitable to go into a linked list.
// Initialise with the value.
struct AudioSampleNode* audioSampleNodeConstructor(const char* sampleName, const char* samplePath) {
    // The value to return. This will be the address of a ListNode structure.
    struct AudioSampleNode* newNode;

    // Reserve memory for the node structure.
    newNode = malloc(sizeof(struct AudioSampleNode));

    // Initialise sensible values - not up to this node to decide what it is connected to.

    strcpy(newNode->sampleName, sampleName); // copies sample_name into the name member of the newNode.

    newNode->sample = al_load_sample(samplePath); // loads the sample from the path.


    newNode->next = NULL;
    newNode->prev = NULL;

    // Return the address of the created node.
    return newNode;
}

// Releases memory associated with the given node.
void audioSampleNodeDestructor(struct AudioSampleNode* node) {
    al_destroy_sample(node->sample);
    free(node);
}

// Reserves and initialises memory for a new list.
// The new list will be composed of linked list nodes
struct AudioSampleList* audioSampleListConstructor() {

    // The value to return. This will be the address of (pointer to) a List structure.
    struct AudioSampleList* audioSampleList;

    // Reserve memory for the list structure.
    audioSampleList = malloc(sizeof(struct AudioSampleList));

    // Initialise sensible default values - on creation it contains no nodes.
    audioSampleList->size = 0;
    audioSampleList->capacity = MAX_NUMBER_SAMPLES;
    audioSampleList->head = NULL;
    audioSampleList->tail = NULL;

    // Return the address of the created list.
    return audioSampleList;
}

// Releases memory associated with the given list.
void audioSampleListDestructor(struct AudioSampleList* audioSampleList) {
    // Free the memory where nodes are stored.
    // This must happen before the list structure memory is free'd.
    // Use these to traverse the list and find the nodes.
    struct AudioSampleNode* currentNode;
    struct AudioSampleNode* nextNode = audioSampleList->head;

    // While there are still nodes in the list
    while (nextNode != NULL) {
        // Move to next node - that is, make it the current one
        currentNode = nextNode;

        // Update where to go after dealing with the current node
        nextNode = currentNode->next;

        // Release the memory associated with the current node
        // Can' do this before the previous step or we would not know where to go next.
        audioSampleNodeDestructor(currentNode);
    }

    // Once all of the nodes have been removed/free'd, finally we can free the list
    free(audioSampleList);
}

// Returns the number of nodes in the list.
int audioSampleListSize(struct AudioSampleList* audioSampleList) {
    return audioSampleList->size;
}

// Returns 1 (true) if the list is empty and 0 (false) otherwise
bool audioSampleListIsEmpty(struct AudioSampleList* audioSampleList) {
    // Use the size function rather than accessing the variable directly.
    // If the way the size is stored changes, this helps to minimise the number of additional changes
    // that would be required.
    if (audioSampleListSize(audioSampleList) == 0) {
        return true;
    }
    else {
        return false;
    }
}

// Returns the first index of an entity whose value is equal to the requested entity.
// If the entity is not found returns -1.
int audioSampleListSearch(struct AudioSampleList* audioSampleList, const char* sampleName) {
    // Use to traverse the list.

    struct AudioSampleNode* currentNode;
    struct AudioSampleNode* nextNode = audioSampleList->head;

    // While there are still nodes in the list...
    // index keeps track of the index so that we can report it.
    int index = 0;
    while (nextNode != NULL) {

        currentNode = nextNode;

        // If the current node has value equal to that given for the search...
        if (strcmp(sampleName, currentNode->sampleName) == 0) {
            // Return the index of the found value.
            return index;
        }

        // Move to next node.
        nextNode = currentNode->next;
        index++;
    }

    // If we have got this far, the value wasn't found, so report not found (-1).
    return -1;
}

// Gets a single node from the list at index.
// Returns NULL if the requested index is invalid.
struct AudioSampleNode* audioSampleListGetNode(struct AudioSampleList* audioSampleList, int index) {
    // Make sure request is valid - not negative and not greater than current count.
    if (index < 0 || index >= audioSampleListSize(audioSampleList)) {
        return NULL;
    }

    // Use to traverse the list
    struct AudioSampleNode* currentNode = audioSampleList->head;

    // We know the index requested, so can iterate up to this number to get the node at that index.
    // We already have the first node (index=0), so start at 1.
    for (int i = 1; i <= index; i++) {
        // Move to next node.
        currentNode = currentNode->next;
    }

    // Now we have the requested node, return its address.
    return currentNode;
}

struct AudioSampleNode* audioSampleListRead(struct AudioSampleList* audioSampleList, const char* sampleName) {

    int index = audioSampleListSearch(audioSampleList, sampleName);

    if(index == -1){
        return NULL;
    }
    else {
        return audioSampleListGetNode(audioSampleList, index);
    }
}

// Add an entity at the end of the list.
// Takes a pointer to a list and a value (entity) to add.
// If the entity was added then 1 (true) is returned. Otherwise 0 (false) is returned.
bool audioSampleListAdd(struct AudioSampleList* audioSampleList, const char* sampleName, const char* samplePath) {

    // Check that the sampleName is not already in the list

    if (audioSampleList->size == audioSampleList->capacity){
        return false;
    }

    if (audioSampleListIsEmpty(audioSampleList) == false && audioSampleListSearch(audioSampleList, sampleName) != -1){

        printf("add sample failed because %s is already used", sampleName);
        return false;
    }

    // Create new list node with value of entity.
    struct AudioSampleNode* newNode = audioSampleNodeConstructor(sampleName, samplePath);

    // Check that the sample was loaded correctly.
    if (newNode->sample == NULL){
        printf("Loading sample %s failed", newNode->sampleName);
        return false;
    }

    // If the list is empty...
    if (audioSampleListIsEmpty(audioSampleList)) {
        // Make the new node the head of the list since it is the only node.
        audioSampleList->head = newNode;
        // Not strictly needed as it is set in the constructor, but for clarity.
        newNode->prev = NULL;
    }
    // Else the list is not empty...
    else {
        // The previous tail of the list is now the node before the new one.
        newNode->prev = audioSampleList->tail;
        // Let the previous tail know about the new node that now comes after it.
        audioSampleList->tail->next = newNode;
    }

    // Make the new node the new tail of the list - always true whether the list is empty or not.
    audioSampleList->tail = newNode;

    // There is always no node after this one as it is the new tail.
    newNode->next = NULL;

    // Always add one to the size of the list.
    audioSampleList->size++;

    // Return 1 (true) to indicate success.
    return true;
}

// Removes an entity from a list at the given index.
void audioSampleListRemove(struct AudioSampleList* audioSampleList, int index) {
    // Get the node at the given index.
    struct AudioSampleNode* audioSampleNode = audioSampleListGetNode(audioSampleList, index);

    // Check to make sure it is valid.
    if (audioSampleNode == NULL) {
        return;
    }

    // If there is a previous node...
    //     ...make it point to the node after this.
    if (audioSampleNode->prev != NULL) {
        audioSampleNode->prev->next = audioSampleNode->next;
    }
    // Else it is the head...
    //    ...so make the next node the head.
    else {
        audioSampleList->head = audioSampleNode->next;
        audioSampleNode->next->prev = NULL;
    }

    // If there is a next node...
    //     ...make it point to the node before this.
    if (audioSampleNode->next != NULL) {
        audioSampleNode->next->prev = audioSampleNode->prev;
    }
    // Else it is the tail...
    //     ...so make the previous node the tail.
    else {
        audioSampleList->tail = audioSampleNode->prev;
        audioSampleNode->prev->next = NULL;
    }

    // There should now be no pointers to the node to be removed anywhere in the list structure,
    // so we can release the memory associated with this node.
    audioSampleNodeDestructor(audioSampleNode);

    // Update the node count.
    audioSampleList->size--;

    return;
}

void audioSampleListDisplay(struct AudioSampleList* audioSampleList){

    printf("List size = %d\n", audioSampleListSize(audioSampleList));

    struct AudioSampleNode* nextNode = audioSampleList->head;

    struct AudioSampleNode* currentNode = nextNode;

    int index = 0;
    while(nextNode != NULL){
        currentNode = nextNode;
        printf("index %d, name = %s, address = %p\n", index, currentNode->sampleName, currentNode->sample);
        nextNode = currentNode->next;
        index++;
    }
}

// AUDIO INSTANCE LIST FUNCTIONS

// Create a new node suitable to go into a linked list.
// Initialise with the value.
struct AudioInstanceNode* audioInstanceNodeConstructor(ALLEGRO_SAMPLE* sample, uint8_t type, float volume) {
    // The value to return. This will be the address of a ListNode structure.
    struct AudioInstanceNode* newNode;

    // Reserve memory for the node structure.
    newNode = malloc(sizeof(struct AudioInstanceNode));

    // Initialise sensible values - not up to this node to decide what it is connected to.

    newNode->sampleInstance = al_create_sample_instance(sample); // loads the sample from the path.
    newNode->state = START;
    newNode->type = type;
    newNode->volume = volume;

    newNode->next = NULL;
    newNode->prev = NULL;

    // Return the address of the created node.
    return newNode;
}

// Releases memory associated with the given node.
void audioInstanceNodeDestructor(struct AudioInstanceNode* audioInstanceNode) {
    al_destroy_sample_instance(audioInstanceNode->sampleInstance);
    free(audioInstanceNode);
}

// Reserves and initialises memory for a new list.
// The new list will be composed of linked list nodes
struct AudioInstanceList* audioInstanceListConstructor(void) {

    // The value to return. This will be the address of (pointer to) a List structure.
    struct AudioInstanceList* audioInstanceList;

    // Reserve memory for the list structure.
    audioInstanceList = malloc(sizeof(struct AudioInstanceList));

    // Initialise sensible default values - on creation it contains no nodes.
    audioInstanceList->size = 0;
    audioInstanceList->capacity = MAX_NUMBER_INSTANCES;
    audioInstanceList->head = NULL;
    audioInstanceList->tail = NULL;

    // Return the address of the created list.
    return audioInstanceList;
}

// Releases memory associated with the given list.
void audioInstanceListDestructor(struct AudioInstanceList* audioInstanceList) {
    // Free the memory where nodes are stored.
    // This must happen before the list structure memory is free'd.
    // Use these to traverse the list and find the nodes.
    struct AudioInstanceNode* currentNode;
    struct AudioInstanceNode* nextNode = audioInstanceList->head;

    // While there are still nodes in the list
    while (nextNode != NULL) {
        // Move to next node - that is, make it the current one
        currentNode = nextNode;

        // Update where to go after dealing with the current node
        nextNode = currentNode->next;

        // Release the memory associated with the current node
        // Can' do this before the previous step or we would not know where to go next.
        audioInstanceNodeDestructor(currentNode);
    }

    // Once all of the nodes have been removed/free'd, finally we can free the list
    free(audioInstanceList);
}

// Returns the number of nodes in the list.
int audioInstanceListSize(struct AudioInstanceList* audioInstanceList) {
    return audioInstanceList->size;
}

// Returns 1 (true) if the list is empty and 0 (false) otherwise
bool audioInstanceListIsEmpty(struct AudioInstanceList* audioInstanceList) {
    // Use the size function rather than accessing the variable directly.
    // If the way the size is stored changes, this helps to minimise the number of additional changes
    // that would be required.
    if (audioInstanceListSize(audioInstanceList) == 0) {
        return true;
    }
    else {
        return false;
    }
}

// Gets a single node from the list at index.
// Returns NULL if the requested index is invalid.
struct AudioInstanceNode* audioInstanceListGetNode(struct AudioInstanceList* audioInstanceList, int index) {
    // Make sure request is valid - not negative and not greater than current count.
    if (index < 0 || index >= audioInstanceListSize(audioInstanceList)) {
        return NULL;
    }

    // Use to traverse the list
    struct AudioInstanceNode* currentNode = audioInstanceList->head;

    // We know the index requested, so can iterate up to this number to get the node at that index.
    // We already have the first node (index=0), so start at 1.
    for (int i = 1; i <= index; i++) {
        // Move to next node.
        currentNode = currentNode->next;
    }

    // Now we have the requested node, return its address.
    return currentNode;
}

// Add an entity at the end of the list.
// Takes a pointer to a list and a value (entity) to add.
// If the entity was added then 1 (true) is returned. Otherwise 0 (false) is returned.
bool audioInstanceListAdd(struct AudioInstanceList* audioInstanceList, ALLEGRO_SAMPLE* sample, uint8_t type, float volume) {


    if (audioInstanceList->size == audioInstanceList->capacity){
        return false;
    }


    // Create new list node with value of entity.
    struct AudioInstanceNode* newNode = audioInstanceNodeConstructor(sample, type, volume);

    // If the list is empty...
    if (audioInstanceListIsEmpty(audioInstanceList)) {
        // Make the new node the head of the list since it is the only node.
        audioInstanceList->head = newNode;
        // Not strictly needed as it is set in the constructor, but for clarity.
        newNode->prev = NULL;
    }
    // Else the list is not empty...
    else {
        // The previous tail of the list is now the node before the new one.
        newNode->prev = audioInstanceList->tail;
        // Let the previous tail know about the new node that now comes after it.
        audioInstanceList->tail->next = newNode;
    }

    // Make the new node the new tail of the list - always true whether the list is empty or not.
    audioInstanceList->tail = newNode;

    // There is always no node after this one as it is the new tail.
    newNode->next = NULL;

    // Always add one to the size of the list.
    audioInstanceList->size++;

    // Return 1 (true) to indicate success.
    return true;
}

// Removes an entity from a list at the given index.
void audioInstanceListRemove(struct AudioInstanceList* audioInstanceList, int index) {
    // Get the node at the given index.
    struct AudioInstanceNode* audioInstanceNode = audioInstanceListGetNode(audioInstanceList, index);

    // Check to make sure it is valid.
    if (audioInstanceNode == NULL) {
        return;
    }

    // If there is a previous node...
    //     ...make it point to the node after this.
    if (audioInstanceNode->prev != NULL) {
        audioInstanceNode->prev->next = audioInstanceNode->next;
    }
    // Else it is the head...
    //    ...so make the next node the head.
    else {
        audioInstanceList->head = audioInstanceNode->next;
        audioInstanceNode->next->prev = NULL;
    }

    // If there is a next node...
    //     ...make it point to the node before this.
    if (audioInstanceNode->next != NULL) {
        audioInstanceNode->next->prev = audioInstanceNode->prev;
    }
    // Else it is the tail...
    //     ...so make the previous node the tail.
    else {
        audioInstanceList->tail = audioInstanceNode->prev;
        audioInstanceNode->prev->next = NULL;
    }

    // There should now be no pointers to the node to be removed anywhere in the list structure,
    // so we can release the memory associated with this node.
    audioInstanceNodeDestructor(audioInstanceNode);

    // Update the node count.
    audioInstanceList->size--;

    return;
}

void audioInstanceListDisplay(struct AudioInstanceList* audioInstanceList){

    printf("List size = %d\n", audioInstanceListSize(audioInstanceList));

    struct AudioInstanceNode* nextNode = audioInstanceList->head;

    struct AudioInstanceNode* currentNode = nextNode;

    int index = 0;
    while(nextNode != NULL){
        currentNode = nextNode;
        printf("index %d, state = %d, type = %d, volume = %f\n", index, currentNode->state, currentNode->type, currentNode->volume);
        nextNode = currentNode->next;
        index++;
    }
}

// GLOBAL VARIABLES
ALLEGRO_MIXER* mixer;
ALLEGRO_VOICE* voice;

struct AudioSampleList* audioSampleList;
struct AudioInstanceList* audioInstanceList;


// USER FUNCTIONS
void amio_init_audio(void){

    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(MAX_NUMBER_SAMPLES);

    audioInstanceList = audioInstanceListConstructor();
    audioSampleList = audioSampleListConstructor();

    mixer = al_create_mixer(44100, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_2);
    voice = al_create_voice(44100, ALLEGRO_AUDIO_DEPTH_INT16, ALLEGRO_CHANNEL_CONF_2);

    al_attach_mixer_to_voice(mixer, voice);
}

void amio_load_sample(const char* sample_name, const char* sample_path){
    audioSampleListAdd(audioSampleList, sample_name, sample_path);
}

/*
 * Function to add a new audio sample to the array of audio instances
 * if there is a free spot.
 */
void amio_add_sample_instance(const char* sample_name, uint8_t type, float volume){

    struct AudioSampleNode* audioSampleNode = audioSampleListRead(audioSampleList,sample_name);

    audioInstanceListAdd(audioInstanceList, audioSampleNode->sample, type, volume);
}

void amio_update_audio(void){

    struct AudioInstanceNode* nextNode = audioInstanceList->head;

    struct AudioInstanceNode* currentNode;

    int index = 0;

    while(nextNode != NULL){

        currentNode = nextNode;

        nextNode = currentNode->next;

        // check if any of the state is START

        if (currentNode->state == START){
            if (currentNode->type == PLAY_ONCE){
                al_set_sample_instance_playmode(currentNode->sampleInstance, ALLEGRO_PLAYMODE_ONCE);
            }

            if (currentNode->type == PLAY_LOOP){
                al_set_sample_instance_playmode(currentNode->sampleInstance, ALLEGRO_PLAYMODE_LOOP);
            }

            al_set_sample_instance_gain(currentNode->sampleInstance, currentNode->volume);

            al_set_sample_instance_position(currentNode->sampleInstance, 0); // set position of audio to zero

            al_attach_sample_instance_to_mixer(currentNode->sampleInstance, mixer);

            if(!al_play_sample_instance(currentNode->sampleInstance)){
                printf("Play sample failed!\n");
            }

            currentNode->state = PLAYING;
        }
        else {
            if (!al_get_sample_instance_playing(currentNode->sampleInstance)){
                audioInstanceListRemove(audioInstanceList, index);
                index--; // by removing the node the index has also decreased.
            }
        }

        index++;
    }
}

void amio_destroy_audio(void){
    audioInstanceListDestructor(audioInstanceList);
    audioSampleListDestructor(audioSampleList);
    al_destroy_mixer(mixer);
    al_destroy_voice(voice);
}
