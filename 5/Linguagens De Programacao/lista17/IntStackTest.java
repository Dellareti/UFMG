/**
 * Test class for IntStack implementation
 */
public class IntStackTest {
    public static void main(String[] args) {
        testEmptyStack();
        testEmptyPop();
        testNormalOperations();
        testLargeOperations();
        testMixedOperations();
    }

    private static void testEmptyStack() {
        System.out.println("=== Teste 1: Pilha vazia ===");
        IntStack stack = new IntStack();
        System.out.println("hasMore(): " + stack.hasMore());  // Deve imprimir false
        System.out.println("Tamanho: " + stack.size());       // Deve imprimir 0
        System.out.println();
    }

    private static void testEmptyPop() {
        System.out.println("=== Teste 2: Pop em pilha vazia ===");
        IntStack stack = new IntStack();
        try {
            stack.pop();
            System.out.println("ERRO: Deveria ter lançado EmptyStackException");
        } catch (EmptyStackException e) {
            System.out.println("OK: " + e.getMessage());
        }
        System.out.println();
    }

    private static void testNormalOperations() {
        System.out.println("=== Teste 3: Operações push/pop normais ===");
        IntStack stack = new IntStack();
        
        System.out.println("Inserindo números 1, 2, 3");
        stack.push(1);
        stack.push(2);
        stack.push(3);
        System.out.println("Tamanho após pushes: " + stack.size());
        
        System.out.println("Removendo elementos:");
        while (stack.hasMore()) {
            System.out.println("Pop: " + stack.pop());
        }
        System.out.println();
    }

    private static void testLargeOperations() {
        System.out.println("=== Teste 4: Muitos pushes (teste de memória) ===");
        IntStack stack = new IntStack();
        try {
            System.out.println("Tentando inserir 1000000 números");
            for (int i = 0; i < 1000000; i++) {
                stack.push(i);
            }
            System.out.println("Push de 1000000 elementos realizado com sucesso");
            System.out.println("Tamanho final: " + stack.size());
        } catch (OutOfMemoryError e) {
            System.out.println("Erro de memória após " + stack.size() + " elementos");
            System.out.println("OK: " + e.getMessage());
        }
        System.out.println();
    }

    private static void testMixedOperations() {
        System.out.println("=== Teste 5: Sequência de operações mistas ===");
        IntStack stack = new IntStack();
        
        stack.push(100);
        System.out.println("Push: 100");
        stack.push(200);
        System.out.println("Push: 200");
        System.out.println("Pop: " + stack.pop());
        stack.push(300);
        System.out.println("Push: 300");
        
        System.out.println("Elementos restantes:");
        while (stack.hasMore()) {
            System.out.println(stack.pop());
        }
        System.out.println();
    }
}