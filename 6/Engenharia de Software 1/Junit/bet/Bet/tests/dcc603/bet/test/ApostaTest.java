package dcc603.bet.test;

import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.Test;
import dcc603.bet.*;

class ApostaTest {
    
    @Test
    void testCriacaoAposta() {
    	
        // dado que eu tenho...
        TipoAposta tipo = TipoAposta.VENCEDOR;
        String palpite = "Time A";
        double valor = 100.0;
        double probabilidade = 50.0;

        // quando eu faco...
        Aposta aposta = new Aposta(tipo, palpite, valor, probabilidade);

        // entao eu espero que aconteca...
        assertEquals(tipo, aposta.getTipo());
        assertEquals(palpite, aposta.getPalpite());
        assertTrue(aposta.estaAberta());
        assertEquals(50.0, aposta.obterProbabilidade());
    }

    @Test
    void testLimiteApostador() {
        
    	// dado que eu tenho...
        Apostador apostador = new Apostador("João");
        
        // quando eu faco...
        boolean[] resultados = new boolean[11];
        for(int i = 0; i < 11; i++) {
            resultados[i] = apostador.fazerAposta(
                new Aposta(TipoAposta.VENCEDOR, "Time A", 100.0, 50.0)
            );
        }

        // entao eu espero que aconteca...
        for(int i = 0; i < 10; i++) {
            assertTrue(resultados[i]);
        }
        assertFalse(resultados[10]);
    }
    
    @Test
    void testCalculoPremio() {
    	
        // dado que eu tenho...
        Aposta aposta = new Aposta(TipoAposta.VENCEDOR, "Time A", 100.0, 50.0);

        // quando eu faco...
        double premio = aposta.getPremio();

        // entao eu espero que aconteca...
        assertEquals(200.0, premio, "O prêmio deve ser 200 (100 * 100/50)");
    }

    @Test
    void testFechamentoAposta() {
    	
        // dado que eu tenho...
        Aposta aposta = new Aposta(TipoAposta.PLACAR_EXATO, "2x1", 100.0, 25.0);

        // quando eu faco...
        assertTrue(aposta.estaAberta(), "A aposta deve estar aberta inicialmente");
        aposta.fecharAposta();

        // entao eu espero que aconteca...
        assertFalse(aposta.estaAberta(), "A aposta deve estar fechada após fecharAposta()");
    }
    
    @Test
    void testAumentoProbabilidadeEPremio() {
    	
        // dado que eu tenho...
        Aposta aposta = new Aposta(TipoAposta.CARTOES_AMARELOS, "3", 100.0, 25.0);
        double premioInicial = aposta.getPremio();
        
        // quando eu faco...
        aposta.aumentarProbabilidade(25.0); // Aumenta para 50%
        double premioAposAumento = aposta.getPremio();
        
        // entao eu espero que aconteca...
        assertEquals(50.0, aposta.obterProbabilidade(), "A probabilidade deve ser 50%");
        assertTrue(premioAposAumento < premioInicial, "O prêmio deve diminuir com o aumento da probabilidade");
        assertEquals(200.0, premioAposAumento, "O prêmio deve ser 200 (100 * 100/50)");
    }
}