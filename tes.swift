import Foundation


func somar(a: Int, b: Int) -> Int {
    return a + b
}


print("Olá, Swift no VS Code!")


let resultado = somar(a: 5, b: 3)
print("O resultado da soma é: \(resultado)")


struct Usuario {
    let nome: String
    let idade: Int
}

let usuario = Usuario(nome: "Maria", idade: 30)
print("Usuário: \(usuario.nome), Idade: \(usuario.idade)")
