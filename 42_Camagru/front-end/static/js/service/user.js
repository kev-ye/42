import HttpClient from "../Common/HttpClient.js";

const http = new HttpClient();
const urlUser = '/api/users'

/* Views */

export async function userInfo() {
  const token = localStorage.getItem('__token__');
  if (!token)
    return undefined;

  const userInfo = await http.get(`${urlUser}/user`, {
    'authorization': `Bearer ${token}`
  }).then(data => data);

  return Object.entries(userInfo).length === 0 ? undefined : userInfo;
}

export async function updateUser(u, p, oldP, m, n) {
  const token = localStorage.getItem('__token__');
  if (!token)
    return undefined;

  const user = await userInfo().then(info => info);
  if (Object.entries(user).length === 0) return {};

  const updateInfo = await http.put(`${urlUser}/update/${user.username}`, {
    "username": u ? u : user.username,
    "password": p ? p : undefined,
    "email": m ? m : user.email,
    "_oldPassword": oldP ? oldP : undefined,
    "notify": n === undefined? true : n
  }, {
    'authorization': `Bearer ${token}`
  }).then(res => res);

  return Object.entries(updateInfo).length === 0 ? undefined : updateInfo;
}

/* Modals */

export async function createNewUser(u, p, m) {
  const res = await http.post(`${urlUser}/create`, {
    "username": u,
    "password": p,
    "email": m
  }).then(data => data);

  return res ? res.created : false;
}