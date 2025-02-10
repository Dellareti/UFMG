public class HeapManager {
    private static final int NULL = -1;
    private int[] memory;
    private int freeStart;

    public HeapManager(int[] initialMemory) {
        this.memory = initialMemory;
        this.memory[0] = memory.length;
        this.memory[1] = NULL;
        freeStart = 0;
    }

    public int allocate(int n) {
        int size = n + 1;
        int p = this.freeStart;
        int previousP = NULL;
        
        while (p != NULL && this.memory[p] < size) {
            previousP = p;
            p = this.memory[p+1];
        }

        if (p == NULL) throw new OutOfMemoryError();

        int nextFree = this.memory[p+1];
        int remaining = this.memory[p] - size;
        
        if (remaining > 1) {
            this.memory[p] = size;
            nextFree = p + size;
            this.memory[nextFree] = remaining;
            this.memory[nextFree+1] = this.memory[p+1];
        }

        if (previousP == NULL)
            this.freeStart = nextFree;
        else
            this.memory[previousP + 1] = nextFree;

        return p + 1;
    }

    public void deallocate(int contentAddress) {
        int blockAddress = contentAddress - 1;
        this.memory[contentAddress] = freeStart;
        this.freeStart = blockAddress;
    }
}