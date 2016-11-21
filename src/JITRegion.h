//
//  JITRegion.h
//  DarwinDiversions
//
//  Created by satori
//  Copyright © 2016 satori. All rights reserved.
//

#include <sys/mman.h>
#include <sys/types.h>

// TODO: this could have more meat to it
class JITRegion {
public:
    // XXX: MAP_JIT will prob fail on iOS
    // possible fix is map RW -> RX
    static JITRegion *CreateRegion(size_t size) {
        void *map = mmap(nullptr, size, PROT_READ | PROT_WRITE | PROT_EXEC,
                         MAP_ANON | MAP_JIT | MAP_PRIVATE, -1, 0);

        if (map == MAP_FAILED) {
            return nullptr;
        }
        return new JITRegion(map, size);
    }

    void *base() const { return _base; }
    size_t size() const { return _size; }

    // TODO: possibly have a Remap(JITRegion *, size) func?
private:
    JITRegion(void *ptr, size_t size) : _base(ptr), _size(size) {}
    void *_base;
    size_t _size;
};
