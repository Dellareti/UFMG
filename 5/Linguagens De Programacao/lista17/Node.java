/**
 * A Node is an object that holds an int and a link
 * to the next Node.  It can be used to build linked
 * lists of ints.
 */
public class Node {
  private int data; // Each node has an int...
  private Node link;   // ...and a link to the next Node

  /**
   * Node constructor.
   * @param theData the int to store in this Node
   * @param theLink a link to the next Node
   */
  public Node(int theData, Node theLink) {
    data = theData;
    link = theLink;
  }
  
  /**
   * Accessor for the int data stored in this Node.
   * @return our int item
   */
  public int getData() {
    return data;
  }
  
  /**
   * Accessor for the link to the next Node.
   * @return the next Node
   */
  public Node getLink() {
    return link;
  }
}
