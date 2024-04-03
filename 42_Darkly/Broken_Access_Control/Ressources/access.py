import requests

def _getName(line):
  return line[line.find('href="') + 6 : line.find('">') if line.find('README') != 0 else line.find('/"')]

def linesParsing(index):
  linesArray = index.text.split('\n');
  lines = filter(lambda line: '<a' in line and '../' not in line, linesArray)
  newLines = map(_getName, lines)
  return newLines

def _getContent(url):
  newReq = requests.get(url)
  if newReq.status_code == 404:
    return None
  return newReq.text

def addResToArray(url):
  result = _getContent(url);
  if result != None:
    readmeArray.append(result[:-1])
    f.write(result);
    print(url, ': ', result[:-1]);

def recursive(url):
  addResToArray(url + 'README')
  req = requests.get(url)
  index = list(linesParsing(req))
  for i in index:
    if i != 'README':
      recursive(url + i)
    else:
      addResToArray(url + i + 'README')
      return

url = 'http://192.168.56.101/.hidden/'
readmeArray = []
f = open("result.txt", "w")

recursive(url)

f.close()