import zeep

def main():
    wsdl_url = "http://www.dneonline.com/calculator.asmx?WSDL"
    soap = zeep.Client(wsdl=wsdl_url) 
    result = soap.service.Add(5, 5)
    print(result)
    result = soap.service.Multiply(5, 5)
    print(result)
    

if __name__ == '__main__':
    main()

