package dcc603.bet;

public class HistoricoPartida {
    private String timeLocal;
    private String timeVisitante;
    private int golsLocal;
    private int golsVisitante;
    private int cartoesAmarelos;

    public HistoricoPartida(String timeLocal, String timeVisitante, 
                          int golsLocal, int golsVisitante, 
                          int cartoesAmarelos) {
        this.timeLocal = timeLocal;
        this.timeVisitante = timeVisitante;
        this.golsLocal = golsLocal;
        this.golsVisitante = golsVisitante;
        this.cartoesAmarelos = cartoesAmarelos;
    }

    public boolean verificarResultado(TipoAposta tipo, String palpite) {
        switch (tipo) {
            case VENCEDOR:
                String vencedor = golsLocal > golsVisitante ? timeLocal : 
                                golsLocal < golsVisitante ? timeVisitante : "EMPATE";
                return vencedor.equals(palpite);
            case PLACAR_EXATO:
                return (golsLocal + "x" + golsVisitante).equals(palpite);
            case CARTOES_AMARELOS:
                return String.valueOf(cartoesAmarelos).equals(palpite);
            default:
                return false;
        }
    }
}