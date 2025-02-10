public class ExceptionBehaviors {
    // a) Try e finally completam normalmente
    public static void caseA() {
        try {
            System.out.println("Try block");
        } finally {
            System.out.println("Finally block");
        }
        // Output:
        // Try block
        // Finally block
    }

    // b) Try completa normalmente, finally lança exceção
    public static void caseB() {
        try {
            System.out.println("Try block");
        } finally {
            throw new RuntimeException("Exception in finally");
        }
        // Output:
        // Try block
        // RuntimeException: Exception in finally
    }

    // c) Try completa normalmente, finally executa return
    public static int caseC() {
        try {
            System.out.println("Try block");
            return 1;
        } finally {
            return 2;  // Este valor sobrescreve o return do try
        }
        // Output:
        // Try block
        // Returns: 2
    }

    // d) Try lança exceção não capturada, finally completa normalmente
    public static void caseD() {
        try {
            throw new RuntimeException("Exception in try");
        } finally {
            System.out.println("Finally block");
        }
        // Output:
        // Finally block
        // RuntimeException: Exception in try
    }

    // e) Try lança exceção não capturada, finally lança outra exceção
    public static void caseE() {
        try {
            throw new RuntimeException("First exception");
        } finally {
            throw new IllegalStateException("Second exception");
        }
        // Output:
        // IllegalStateException: Second exception
    }

    // f) Try lança exceção não capturada, finally executa return
    public static int caseF() {
        try {
            throw new RuntimeException("Exception in try");
        } finally {
            return 42;  // Este return "engole" a exceção
        }
        // Output:
        // Returns: 42
    }

    // g) Try lança exceção que é capturada, catch e finally completam normalmente
    public static void caseG() {
        try {
            throw new RuntimeException("Exception in try");
        } catch (RuntimeException e) {
            System.out.println("Caught: " + e.getMessage());
        } finally {
            System.out.println("Finally block");
        }
        // Output:
        // Caught: Exception in try
        // Finally block
    }

    // h) Try lança exceção que é capturada, catch completa, finally lança exceção
    public static void caseH() {
        try {
            throw new RuntimeException("First exception");
        } catch (RuntimeException e) {
            System.out.println("Caught exception");
        } finally {
            throw new IllegalStateException("Finally exception");
        }
        // Output:
        // Caught exception
        // IllegalStateException: Finally exception
    }

    // i) Try lança exceção que é capturada, catch completa, finally retorna
    public static int caseI() {
        try {
            throw new RuntimeException("Exception");
        } catch (RuntimeException e) {
            return 1;
        } finally {
            return 2;  // Este valor sobrescreve o return do catch
        }
        // Output:
        // Returns: 2
    }

    // j) Try lança exceção capturada, catch lança outra, finally completa
    public static void caseJ() {
        try {
            throw new RuntimeException("First");
        } catch (RuntimeException e) {
            throw new IllegalStateException("Second");
        } finally {
            System.out.println("Finally block");
        }
        // Output:
        // Finally block
        // IllegalStateException: Second
    }

    // k) Try lança exceção, catch lança outra, finally lança uma terceira
    public static void caseK() {
        try {
            throw new RuntimeException("First");
        } catch (RuntimeException e) {
            throw new IllegalStateException("Second");
        } finally {
            throw new IllegalArgumentException("Third");
        }
        // Output:
        // IllegalArgumentException: Third
    }

    // l) Try lança exceção, catch lança outra, finally retorna
    public static int caseL() {
        try {
            throw new RuntimeException("First");
        } catch (RuntimeException e) {
            throw new IllegalStateException("Second");
        } finally {
            return 42;  // Este return "engole" todas as exceções anteriores
        }
        // Output:
        // Returns: 42
    }

    // m) Try lança exceção, catch retorna, finally completa
    public static int caseM() {
        try {
            throw new RuntimeException();
        } catch (RuntimeException e) {
            return 1;
        } finally {
            System.out.println("Finally block");
        }
        // Output:
        // Finally block
        // Returns: 1
    }

    // n) Try lança exceção, catch retorna, finally lança exceção
    public static int caseN() {
        try {
            throw new RuntimeException();
        } catch (RuntimeException e) {
            return 1;
        } finally {
            throw new IllegalStateException();
        }
        // Output:
        // IllegalStateException
    }

    // o) Try lança exceção, catch retorna valor, finally retorna outro valor
    public static int caseO() {
        try {
            throw new RuntimeException();
        } catch (RuntimeException e) {
            return 1;
        } finally {
            return 2;
        }
        // Output:
        // Returns: 2
    }

    // p) Try retorna valor, finally completa normalmente
    public static int caseP() {
        try {
            return 1;
        } finally {
            System.out.println("Finally block");
        }
        // Output:
        // Finally block
        // Returns: 1
    }

    // q) Try retorna valor, finally lança exceção
    public static int caseQ() {
        try {
            return 1;
        } finally {
            throw new RuntimeException("Finally exception");
        }
        // Output:
        // RuntimeException: Finally exception
    }

    // r) Try retorna valor, finally retorna outro valor
    public static int caseR() {
        try {
            return 1;
        } finally {
            return 2;
        }
        // Output:
        // Returns: 2
    }

  public static void main(String[] args) {
        System.out.println("===== TESTES DE COMPORTAMENTO TRY-CATCH-FINALLY =====\n");

        // Caso A
        System.out.println("Caso A - Try e finally completam normalmente:");
        caseA();
        System.out.println("----------------------------------------\n");

        // Caso B
        System.out.println("Caso B - Try completa normalmente, finally lança exceção:");
        try {
            caseB();
        } catch (Exception e) {
            System.out.println("Exceção capturada: " + e.getMessage());
        }
        System.out.println("----------------------------------------\n");

        // Caso C
        System.out.println("Caso C - Try completa normalmente, finally executa return:");
        int resultC = caseC();
        System.out.println("Valor retornado: " + resultC);
        System.out.println("----------------------------------------\n");

        // Caso D
        System.out.println("Caso D - Try lança exceção não capturada, finally completa:");
        try {
            caseD();
        } catch (Exception e) {
            System.out.println("Exceção capturada: " + e.getMessage());
        }
        System.out.println("----------------------------------------\n");

        // Caso E
        System.out.println("Caso E - Try e finally lançam exceções diferentes:");
        try {
            caseE();
        } catch (Exception e) {
            System.out.println("Exceção capturada: " + e.getMessage());
        }
        System.out.println("----------------------------------------\n");

        // Caso F
        System.out.println("Caso F - Try lança exceção, finally retorna valor:");
        int resultF = caseF();
        System.out.println("Valor retornado: " + resultF);
        System.out.println("----------------------------------------\n");

        // Caso G
        System.out.println("Caso G - Try lança exceção capturada, todos completam:");
        caseG();
        System.out.println("----------------------------------------\n");

        // Caso H
        System.out.println("Caso H - Try lança exceção, finally lança outra:");
        try {
            caseH();
        } catch (Exception e) {
            System.out.println("Exceção capturada: " + e.getMessage());
        }
        System.out.println("----------------------------------------\n");

        // Caso I
        System.out.println("Caso I - Try lança exceção, catch retorna, finally retorna:");
        int resultI = caseI();
        System.out.println("Valor retornado: " + resultI);
        System.out.println("----------------------------------------\n");

        // Caso J
        System.out.println("Caso J - Catch lança exceção, finally completa:");
        try {
            caseJ();
        } catch (Exception e) {
            System.out.println("Exceção capturada: " + e.getMessage());
        }
        System.out.println("----------------------------------------\n");

        // Caso K
        System.out.println("Caso K - Try, catch e finally lançam exceções:");
        try {
            caseK();
        } catch (Exception e) {
            System.out.println("Exceção capturada: " + e.getMessage());
        }
        System.out.println("----------------------------------------\n");

        // Caso L
        System.out.println("Caso L - Try e catch lançam exceções, finally retorna:");
        int resultL = caseL();
        System.out.println("Valor retornado: " + resultL);
        System.out.println("----------------------------------------\n");

        // Caso M
        System.out.println("Caso M - Try lança exceção, catch retorna, finally completa:");
        int resultM = caseM();
        System.out.println("Valor retornado: " + resultM);
        System.out.println("----------------------------------------\n");

        // Caso N
        System.out.println("Caso N - Catch retorna, finally lança exceção:");
        try {
            caseN();
        } catch (Exception e) {
            System.out.println("Exceção capturada: " + e.getMessage());
        }
        System.out.println("----------------------------------------\n");

        // Caso O
        System.out.println("Caso O - Catch e finally retornam valores diferentes:");
        int resultO = caseO();
        System.out.println("Valor retornado: " + resultO);
        System.out.println("----------------------------------------\n");

        // Caso P
        System.out.println("Caso P - Try retorna, finally completa normalmente:");
        int resultP = caseP();
        System.out.println("Valor retornado: " + resultP);
        System.out.println("----------------------------------------\n");

        // Caso Q
        System.out.println("Caso Q - Try retorna, finally lança exceção:");
        try {
            caseQ();
        } catch (Exception e) {
            System.out.println("Exceção capturada: " + e.getMessage());
        }
        System.out.println("----------------------------------------\n");

        // Caso R
        System.out.println("Caso R - Try e finally retornam valores diferentes:");
        int resultR = caseR();
        System.out.println("Valor retornado: " + resultR);
        System.out.println("----------------------------------------\n");
    }
  }
