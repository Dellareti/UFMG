/**
 * Exception thrown when attempting to pop from an empty stack
 */
public class EmptyStackException extends RuntimeException {
    public EmptyStackException() {
        super("Cannot pop from an empty stack");
    }
}