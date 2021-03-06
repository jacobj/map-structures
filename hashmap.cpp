#include "hashmap.hpp"

HashMap::HashMap(std::size_t max_size) {
    this->backing_array = new pair*[max_size];
    this->size = 0;
    this->max_size = max_size;
    for ( int i = 0; i != max_size; ++i )
        backing_array[i] = nullptr;
}

HashMap::~HashMap() {
    delete[] backing_array;
}

int HashMap::hash( int key ) {
    return ( (int) key % max_size );
}

bool HashMap::insert( int key, char value ) {
    if ( size == max_size ) {
        return false;
    }
    pair* item = new pair( key, value );
    int index = hash(key);
    if ( this->backing_array[index] == nullptr ) {
        this->backing_array[index] = item;
        ++size;
        return true;
    } else {
        for ( int i = index + 1; i != index; ++i ) {
            if ( i == max_size ) { // Wrap around
                i = 0;
            }
            if ( backing_array[i] == nullptr ) {
                backing_array[i] = item;
                ++size;
                return true;
            }
        }
        // There's no spot to insert this value.
        return false;
    }
}

bool HashMap::remove( int key, char &value ) {
    int index = hash(key);
    if ( backing_array[index]->key == key ) {
        value = backing_array[index]->value;
        backing_array[index] = nullptr;
        --size;
        for ( int i = index + 1; i != index; ++i ) {
            if ( i == max_size ) {
                i = 0;
            }
            if ( backing_array[i] == nullptr ) {
                break;
            }
            pair* temp = backing_array[i];
            backing_array[i] = nullptr;
            insert( temp->key, temp->value );
        }
        // TODO: This should also clean up clusters.
        return true;
    } else {
         for ( int i = index + 1; i != index; ++i ) {
            if ( i == max_size ) { // Wrap around
                i = 0;
            }
            if ( backing_array[i]->key == key ) {
                 value = backing_array[i]->value;
                 backing_array[i] = nullptr;
                 --size;
                 for ( int j = i + 1; j != i; ++j ) {
                     if ( j == max_size ) {
                         j = 0;
                     }
                     if ( backing_array[j] == nullptr ) {
                         break;
                     }
                     pair* temp = backing_array[j];
                     backing_array[j] = nullptr;
                     insert( temp->key, temp->value );
                 }
                 return true;
            }
         }
         return false;
    }
}

bool HashMap::search( int key, char &value ) {
    int index = hash(key);
    if ( backing_array[index]->key == key ) {
        value = backing_array[index]->value;
        return true;
    } else {
        for ( int i = index + 1; i != index; ++i ) {
            if ( i == max_size )
                i = 0;
            if ( backing_array[i]->key == key ) {
                value = backing_array[i]->value;
                return true;
            }
        }
        return false;
    }
}

void HashMap::clear() {
    for ( int i = 0; i != max_size; ++i ) {
        backing_array[i] = nullptr;
    }
    this->size = 0;
}

bool HashMap::isEmpty() {
    if ( size == 0 ) {
        return true;
    } else {
        return false; 
    }
}

std::size_t HashMap::capacity() {
    return size;
}

std::ostream& HashMap::print( std::ostream& out ) {
    out << "[ ";
    for ( int i = 0; i != max_size; ++i ) {
        if ( backing_array[i] != nullptr ) {
            out << backing_array[i]->key;
        } else {
            out << "-";
        }

        if ( i != max_size - 1 ) {
            out << " | ";
        }
    }
    out << " ]";
    return out;
}
