#include "Allocator.h"

class StackAllocator : public Allocator {
public:
    StackAllocator(size_t size, void *start);
    ~StackAllocator();

    void *allocate(size_t size, u8 alignment) override;
    void deallocate(void *p) override;

private:
    StackAllocator(const StackAllocator &);

    // Prevent copies because it might cause errors
    StackAllocator &operator=(const StackAllocator &);

    struct AllocationHeader {
#if _DEBUG
        void *prev_address;
#endif

        u8 adjustment;
    };

#if _DEBUG
    void *_prev_position;
#endif

    void *_current_pos;
};
