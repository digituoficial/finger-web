# finger-web


* Sobre o código

A função ```getFingerprintID()``` checa se existe a ID salava. Se encontrada ela faz o retorno da ID, do contrario ela retornará -1.


* Configure o sensor

Configure o sensor conforme a tabela

| Cabo Sensor   |    Input Arduino |
|---------------|------------------|
|      Red      |        5v        |
|    Green      |       Digital2   |
|    White      |       Digital3   |
|    Black      |       GND        |

você pode colocar os cabos `Green` e `Black` em qualquer outra porta digital desde que mude no momento  da instancia de `mySerial()`
