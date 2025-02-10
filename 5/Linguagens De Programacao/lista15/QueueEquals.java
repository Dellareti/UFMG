public class Queue implements MyCollection {
    // ... resto da implementação anterior ...
    
    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        if (!(obj instanceof Queue)) {
            return false;
        }
        
        Queue other = (Queue) obj;
        Node thisNode = this.head;
        Node otherNode = other.head;
        
        while (thisNode != null && otherNode != null) {
            if (!thisNode.getValue().equals(otherNode.getValue())) {
                return false;
            }
            thisNode = thisNode.getNext();
            otherNode = otherNode.getNext();
        }
        
        return thisNode == null && otherNode == null;
    }
}
