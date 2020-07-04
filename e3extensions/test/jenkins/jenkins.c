#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

uint32_t jenkins_one_at_a_time_hash(const uint8_t* key, size_t length) {
    size_t i = 0;
    uint32_t hash = 0;
    while (i != length) {
        hash += key[i++];
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    return hash;
}

uint32_t jenkins_ll(const uint8_t* key, size_t length) {
    size_t i = 0;
    uint32_t hash = 0;
    uint32_t temp;
    do {
        temp = key[i];
        i++;
        hash += temp;
        temp = hash << 10;
        hash += temp;
        temp = hash >> 6;
        printf("%u %u %u\n", hash, temp, hash^temp);
        hash ^= temp;
    } while (i != length);
    temp = hash << 3;
    hash += temp;
    temp = hash >> 11;
    printf("%u %u %u\n", hash, temp, hash^temp);
    hash ^= temp;
    temp = hash << 15;
    hash += temp;
    return hash;
}

int main(void) {
    asm("l.debug");
    size_t length = 2;
    uint8_t array[length]; // = malloc(length * sizeof(uint8_t));
    for (int i = 0 ; i < length ; i++) {
        array[i] = i + 1;
    }

    // assert(jenkins_one_at_a_time_hash(array, length) == jenkins_ll(array, length));
    printf("hash : %u\n", jenkins_ll(array, length));
    asm("l.debug");
    return 0;
}
