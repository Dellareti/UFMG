package dcc603.bet;

import java.util.ArrayList;
import java.util.List;
import java.time.LocalDateTime;

public class Partida {
    private List<Aposta> apostas;
    private List<HistoricoPartida> historico;

    public Partida(String timeLocal, String timeVisitante, LocalDateTime dataHora) {
        this.apostas = new ArrayList<>();
        this.historico = new ArrayList<>();
    }

    public void adicionarHistorico(HistoricoPartida historico) {
        this.historico.add(historico);
    }

    public void adicionarAposta(Aposta aposta) {
        apostas.add(aposta);
    }

    public List<Aposta> getApostas() {
        return new ArrayList<>(apostas);
    }

    public double calcularProbabilidade(TipoAposta tipo, String palpite) {
        double probabilidade = historico.stream()
            .filter(h -> h.verificarResultado(tipo, palpite))
            .count() * 100.0 / historico.size();
        
        // Arredonda para 2 casas decimais
        return Math.round(probabilidade * 100.0) / 100.0;
    }
}
