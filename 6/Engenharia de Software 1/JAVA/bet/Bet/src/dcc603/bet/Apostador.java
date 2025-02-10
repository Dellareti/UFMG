package dcc603.bet;

import java.util.ArrayList;
import java.util.List;

public class Apostador {
    private String nome;
    private List<Aposta> apostas;
    public static final int LIMITE_APOSTAS = 10;

    public Apostador(String nome) {
        this.nome = nome;
        this.apostas = new ArrayList<>();
    }

    public String getNome() {
        return nome;
    }

    public boolean fazerAposta(Aposta aposta) {
        if (apostas.size() < LIMITE_APOSTAS) {
            return apostas.add(aposta);
        }
        return false;
    }

    public List<Aposta> getApostas() {
        return new ArrayList<>(apostas);
    }
}