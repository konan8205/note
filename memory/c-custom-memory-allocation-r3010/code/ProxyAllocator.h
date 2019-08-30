#include "Allocator.h"

class ProxyAllocator : public Allocator {
public:
    ProxyAllocator(Allocator &allocator);
    ~ProxyAllocator();
    void *allocate(size_t size, u8 alignment) override;
    void deallocate(void *p) override;

private:
    ProxyAllocator(const ProxyAllocator &);

    // Prevent copies because it might cause errors
    ProxyAllocator &operator=(const ProxyAllocator &);
    Allocator &_allocator;
};
