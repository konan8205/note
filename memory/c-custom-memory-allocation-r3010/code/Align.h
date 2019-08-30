
using u8 = unsigned char;

inline void *alignForward(void *address, u8 alignment) {
    return (void *)((reinterpret_cast<u8 *>(address) +
                     static_cast<u8>(alignment - 1)) &
                    static_cast<u8>(~(alignment - 1)));
}

inline u8 alignForwardAdjustment(const void *address, u8 alignment) {
    u8 adjustment = alignment - (reinterpret_cast<u8 *>(address) &
                                 static_cast<u8 *>(alignment - 1));
    if (adjustment == alignment)
        return 0;
    // Already aligned
    return adjustment;
}

inline u8 alignForwardAdjustmentWithHeader(const void *address, u8 alignment,
                                           u8 headerSize) {
    u8 adjustment = alignForwardAdjustment(address, alignment);
    u8 neededSpace = headerSize;

    if (adjustment < neededSpace) {
        neededSpace -= adjustment;

        // Increase adjustment to fit header
        adjustment += alignment * (neededSpace / alignment);

        if (neededSpace % alignment > 0)
            adjustment += alignment;
    }

    return adjustment;
}
