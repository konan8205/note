#include "Allocator.h"

class PoolAllocator : public Allocator {
public:
    PoolAllocator(size_t objectSize, u8 objectAlignment, size_t size,
                  void *mem);
    ~PoolAllocator();
    void *allocate(size_t size, u8 alignment) override;
    void deallocate(void *p) override;

private:
    PoolAllocator(const PoolAllocator &);

    // Prevent copies because it might cause errors
    PoolAllocator &operator=(const PoolAllocator &);
    size_t _objectSize;

    u8 _objectAlignment;
    void **_free_list;
};
