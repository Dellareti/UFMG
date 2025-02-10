/**
 * An IntStack is an object that holds a stack of ints.
 */
public class IntStack {
    private Node top = null;
    private int size = 0;

    /**
     * Test whether this stack has more elements.
     * @return true if this stack is not empty
     */
    public boolean hasMore() {
        return (top != null);
    }

    /**
     * Pop the top int from this stack and return it.
     * @return the popped int
     * @throws EmptyStackException if the stack is empty
     */
    public int pop() {
        if (!hasMore()) {
            throw new EmptyStackException();
        }
        Node n = top;
        top = n.getLink();
        size--;
        return n.getData();
    }

    /**
     * Push an int on top of this stack.
     * @param data the int to add
     * @throws OutOfMemoryError if system is out of memory
     */
    public void push(int data) {
        top = new Node(data, top);
        size++;
    }

    /**
     * Get the current size of the stack
     * @return number of elements in the stack
     */
    public int size() {
        return size;
    }
}