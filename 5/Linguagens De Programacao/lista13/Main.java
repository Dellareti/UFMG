public class Main {
    public static void main(String[] args) {
        // Testando IntList
        IntList list1 = new IntList();
        list1.add(10);
        list1.add(20);
        list1.add(30);

        IntList list2 = new IntList();
        list2.add(10);
        list2.add(20);
        list2.add(30);

        System.out.println("Exercício 01: " + list1.contains(20)); // true
        System.out.println("Exercício 02: " + list1.equals(list2)); // true

        IntList appended = list1.append(list2);
        System.out.println("Exercício 03:");
        appended.printList();

        IntList reversed = list1.reverse();
        System.out.println("Exercício 04:");
        reversed.printList();

        list1.reverseMe();
        System.out.println("Exercício 05:");
        list1.printList();

        IntList sorted = reversed.sort();
        System.out.println("Exercício 06:");
        sorted.printList();

        // Testando Int
        Int a = new Int(7);
        Int b = new Int(3);

        System.out.println("Exercício 07c: " + a.toString()); // 7
        System.out.println("Exercício 07d: " + a.plus(b)); // 10
        System.out.println("Exercício 07e: " + a.minus(b)); // 4
        System.out.println("Exercício 07e: " + a.times(b)); // 21
        System.out.println("Exercício 07e: " + a.div(b)); // 2
        System.out.println("Exercício 07f: " + a.isPrime()); // true
    }
}