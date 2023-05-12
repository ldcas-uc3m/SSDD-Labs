import zeep

def main():
    wsdl_url = "http://localhost:8000/?wsdl"
    soap = zeep.Client(wsdl=wsdl_url) 
    result = soap.service.add(5, 5)
    print(result)
    result = soap.service.sub(5, 5)
    print(result)

if __name__ == '__main__':
    main()

