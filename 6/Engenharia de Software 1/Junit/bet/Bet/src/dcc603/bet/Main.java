package dcc603.bet;

import java.time.LocalDateTime;

/**
 * Classe principal para testar o sistema de apostas esportivas
 */
public class Main {
    
    public static void main(String[] args) {
    	
        // Teste 1: Criação de apostador e verificação do limite de apostas

        System.out.println("=== Teste 1: Apostador e Limite de Apostas ===");
        Apostador italo = new Apostador("Ítalo Dell Areti");
        System.out.println("Apostador criado: " + italo.getNome());
        
        for (int i = 0; i < 11; i++) {
            boolean sucesso = italo.fazerAposta(
                new Aposta(TipoAposta.VENCEDOR, "Cruzeiro", 100.0, 50.0)
            );
            System.out.println("Aposta " + (i + 1) + " realizada: " + sucesso);
        }
        System.out.println("Total de apostas: " + italo.getApostas().size());
        System.out.println();

        // Teste 2: Criação de partida e cálculo de probabilidades

        System.out.println("=== Teste 2: Partida e Probabilidades ===");
        Partida partida = new Partida("Cruzeiro", "Atlético", LocalDateTime.now());
        
        // Adicionando histórico
        
        partida.adicionarHistorico(new HistoricoPartida("Cruzeiro", "Atlético", 2, 1, 3));
        partida.adicionarHistorico(new HistoricoPartida("Cruzeiro", "Atlético", 1, 1, 2));
        partida.adicionarHistorico(new HistoricoPartida("Cruzeiro", "Atlético", 2, 0, 4));
        
        double probVitoria = partida.calcularProbabilidade(TipoAposta.VENCEDOR, "Cruzeiro");
        System.out.println("Probabilidade de vitória do Cruzeiro: " + probVitoria + "%");
        System.out.println();

        // Teste 3: Criação de diferentes tipos de apostas

        System.out.println("=== Teste 3: Diferentes Tipos de Apostas ===");
        
        Aposta apostaVencedor = new Aposta(TipoAposta.VENCEDOR, "Cruzeiro", 90.0, probVitoria);
        System.out.printf("Aposta no vencedor - Prêmio possível: R$%.0f%n", apostaVencedor.getPremio());
        
        Aposta apostaPlacar = new Aposta(TipoAposta.PLACAR_EXATO, "2x1", 50.0, 20.0);
        System.out.printf("Aposta no placar - Prêmio possível: R$%.2f%n", apostaPlacar.getPremio());
        
        Aposta apostaCartoes = new Aposta(TipoAposta.CARTOES_AMARELOS, "3", 30.0, 30.0);
        System.out.printf("Aposta nos cartões - Prêmio possível: R$%.2f%n", apostaCartoes.getPremio());

    }
}
