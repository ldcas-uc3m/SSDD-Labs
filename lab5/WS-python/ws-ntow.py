import zeep

wsdl = 'https://www.dataaccess.com/webservicesserver/numberconversion.wso?WSDL'
client = zeep.Client(wsdl=wsdl)
print(client.service.NumberToWords(427))

