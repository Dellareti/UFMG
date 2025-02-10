/**
 * 
 */
package dcc603.bet;

/**
 * @author Eduardo Figueiredo
 *
 * Atencao! Esta classe eh um esqueleto. 
 * Voce pode (e deve) mudar e ampliar a sua implementacao.
 */

public class Aposta {
    public static final int ABERTA = 1;
    public static final int FECHADA = 2;
    
    private TipoAposta tipo;
    private String palpite;
    private double valorAposta;
    protected int status = ABERTA;
    protected double probabilidade = 0;
    private double premio;

    public Aposta(TipoAposta tipo, String palpite, double valorAposta, double probabilidade) {
        this.tipo = tipo;
        this.palpite = palpite;
        this.valorAposta = valorAposta;
        this.probabilidade = probabilidade;
        calcularPremio();
    }

    private void calcularPremio() {
        // Quanto menor a probabilidade, maior o prêmio
     	
    	double premioCalculado = valorAposta * (100 / probabilidade);
         
    	 // Arredonda para 2 casas decimais
         this.premio = Math.round(premioCalculado * 100.0) / 100.0;
    }

    public void aumentarProbabilidade(double incremento) {
        this.probabilidade += incremento;
        calcularPremio();
    }
    
    public double obterProbabilidade() {
        return this.probabilidade;
    }

    public double getPremio() {
        return premio;
    }

    public void fecharAposta() {
        this.status = FECHADA;
    }

    public boolean estaAberta() {
        return this.status == ABERTA;
    }

    public String getPalpite() {
        return palpite;
    }

    public TipoAposta getTipo() {
        return tipo;
    }
}