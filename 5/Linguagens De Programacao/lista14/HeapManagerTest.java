public class HeapManagerTest {
    public static void main(String[] args) {
        testFirstFit();
        System.out.println("\n-------------------\n");
        testBestFit();
    }

    static void testFirstFit() {
        System.out.println("Testando First-Fit:");
        HeapManager hm = new HeapManager(new int[17]);
        try {
            int a = hm.allocate(2);
            System.out.println("Alocou a(2): " + a);
            int b = hm.allocate(1);
            System.out.println("Alocou b(1): " + b);
            int c = hm.allocate(1);
            System.out.println("Alocou c(1): " + c);
            
            hm.deallocate(a);
            System.out.println("Desalocou a");
            hm.deallocate(c);
            System.out.println("Desalocou c");
            
            int d = hm.allocate(1);
            System.out.println("Alocou d(1): " + d);
            int e = hm.allocate(2);
            System.out.println("Alocou e(2): " + e);
        } catch (OutOfMemoryError e) {
            System.out.println("Falha na alocação: " + e.getMessage());
        }
    }

    static void testBestFit() {
        System.out.println("Testando Best-Fit:");
        HeapManagerBestFit hm = new HeapManagerBestFit(new int[17]);
        try {
            int a = hm.allocate(2);
            System.out.println("Alocou a(2): " + a);
            int b = hm.allocate(1);
            System.out.println("Alocou b(1): " + b);
            int c = hm.allocate(1);
            System.out.println("Alocou c(1): " + c);
            
            hm.deallocate(a);
            System.out.println("Desalocou a");
            hm.deallocate(c);
            System.out.println("Desalocou c");
            
            int d = hm.allocate(1);
            System.out.println("Alocou d(1): " + d);
            int e = hm.allocate(2);
            System.out.println("Alocou e(2): " + e);
        } catch (OutOfMemoryError e) {
            System.out.println("Falha na alocação: " + e.getMessage());
        }
    }
}