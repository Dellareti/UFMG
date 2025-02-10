import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class IntList {
    private List<Integer> elements;

    public IntList() {
        this.elements = new ArrayList<>();
    }

    public IntList(List<Integer> elements) {
        this.elements = new ArrayList<>(elements);
    }

    public void add(int value) {
        elements.add(value);
    }

    public boolean contains(int n) {
        return elements.contains(n);
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        IntList other = (IntList) obj;
        return elements.equals(other.elements);
    }

    public IntList append(IntList other) {
        List<Integer> newList = new ArrayList<>(this.elements);
        newList.addAll(other.elements);
        return new IntList(newList);
    }

    public IntList reverse() {
        List<Integer> reversedList = new ArrayList<>(this.elements);
        Collections.reverse(reversedList);
        return new IntList(reversedList);
    }

    public void reverseMe() {
        Collections.reverse(this.elements);
    }

    public IntList sort() {
        List<Integer> sortedList = new ArrayList<>(this.elements);
        Collections.sort(sortedList);
        return new IntList(sortedList);
    }

    public void printList() {
        System.out.println(elements);
    }
}
