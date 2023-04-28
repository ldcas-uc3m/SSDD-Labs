import requests

url = input('Webpage to grab source from: ')

req = requests.get(url, 'html.parser')

print(req.text)
