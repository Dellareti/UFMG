public class HeapManagerBestFit {
    private static final int NULL = -1;
    private int[] memory;
    private int freeStart;

    public HeapManagerBestFit(int[] initialMemory) {
        this.memory = initialMemory;
        this.memory[0] = memory.length;
        this.memory[1] = NULL;
        freeStart = 0;
    }

    public int allocate(int n) {
        int size = n + 1;
        int p = this.freeStart;
        int previousP = NULL;
        int bestFitBlock = NULL;
        int bestFitPrevious = NULL;
        int bestFitSize = Integer.MAX_VALUE;

        while (p != NULL) {
            if (this.memory[p] >= size && this.memory[p] < bestFitSize) {
                bestFitSize = this.memory[p];
                bestFitBlock = p;
                bestFitPrevious = previousP;
                if (bestFitSize == size) break;
            }
            previousP = p;
            p = this.memory[p+1];
        }

        if (bestFitBlock == NULL) throw new OutOfMemoryError();

        int nextFree = this.memory[bestFitBlock+1];
        int remaining = bestFitSize - size;
        
        if (remaining > 1) {
            this.memory[bestFitBlock] = size;
            nextFree = bestFitBlock + size;
            this.memory[nextFree] = remaining;
            this.memory[nextFree+1] = this.memory[bestFitBlock+1];
        }

        if (bestFitPrevious == NULL)
            this.freeStart = nextFree;
        else
            this.memory[bestFitPrevious + 1] = nextFree;

        return bestFitBlock + 1;
    }

    public void deallocate(int contentAddress) {
        int blockAddress = contentAddress - 1;
        this.memory[contentAddress] = freeStart;
        this.freeStart = blockAddress;
    }
}