public class Queue implements MyCollection {
    private Node head; // Início da fila
    private Node tail; // Fim da fila
    
    public Queue() {
        head = null;
        tail = null;
    }
    
    @Override
    public void add(String s) {
        Node newNode = new Node(s, null);
        if (isEmpty()) {
            head = newNode;
        } else {
            tail.next = newNode;
        }
        tail = newNode;
    }
    
    @Override
    public String remove() {
        if (isEmpty()) {
            throw new IllegalStateException("Queue is empty");
        }
        String value = head.getValue();
        head = head.getNext();
        if (head == null) {
            tail = null;
        }
        return value;
    }
    
    @Override
    public boolean isEmpty() {
        return head == null;
    }
}
