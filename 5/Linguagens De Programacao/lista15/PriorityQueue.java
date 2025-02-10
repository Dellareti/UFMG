public class PriorityQueue extends Queue {
    @Override
    public void add(String s) {
        Node newNode = new Node(s, null);
        
        // Se está vazia ou o novo elemento é maior que o head
        if (isEmpty() || s.compareTo(head.getValue()) >= 0) {
            newNode.next = head;
            head = newNode;
            if (tail == null) {
                tail = newNode;
            }
            return;
        }
        
        // Encontra posição correta
        Node current = head;
        while (current.getNext() != null && 
               s.compareTo(current.getNext().getValue()) < 0) {
            current = current.getNext();
        }
        
        // Insere na posição
        newNode.next = current.getNext();
        current.next = newNode;
        if (newNode.next == null) {
            tail = newNode;
        }
    }
}
