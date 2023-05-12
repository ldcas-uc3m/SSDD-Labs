import zeep

SERVICE_ADDRESS = "https://www.w3schools.com/xml/tempconvert.asmx?WSDL"


def to_fahrenheit(number: float) -> float:
    # create client
    client = zeep.Client(wsdl=SERVICE_ADDRESS)

    return client.service.CelsiusToFahrenheit(number)


def to_celsius(number: float) -> float:
    # create client
    client = zeep.Client(wsdl=SERVICE_ADDRESS)

    return client.service.FahrenheitToCelsius(number)



if __name__ == "__main__":

    temperature = 25.3

    print(to_fahrenheit(temperature))
    print(to_celsius(to_fahrenheit(temperature)))