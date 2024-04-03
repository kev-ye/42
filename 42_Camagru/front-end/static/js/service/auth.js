import HttpClient from "../Common/HttpClient.js";

const http = new HttpClient();
const urlAuth = '/api/auth';

/* Views */

export async function isLogin() {
  const token = localStorage.getItem('__token__');
  if (!token) return false;

  const checkLogin = await http.post(`${urlAuth}/verify`, {}, {
    'authorization': `Bearer ${token}`
  }).then(data => data);

  return Object.entries(checkLogin).length !== 0 ? checkLogin : undefined;
}

export async function haveAccess() {
  const access = await isLogin().then(data => data);

  if (!access) return false;
  
  return Object.values(access)[0];
}

export async function tokenVerify() {
  const query = location.search;
  const param = new URLSearchParams(query);
  const token = param.get('token');

  if (!token) return false;

  const verify = await http.get(`${urlAuth}/tokenVerify`, {
    'authorization': `Bearer ${token}`
  }).then(token => token);

  return Object.entries(verify).length !== 0 ? Object.values(verify)[0] : false;
}

export async function resetPassword(token, p) {
  const res = await http.put(`${urlAuth}/reset/change?token=${token}`, {
    "password": p
  }).then(data => data);

  return Object.entries(res).length !== 0 ? Object.values(res)[0] : false;
}

export async function accountConfirmation(token) {
  const res = await http.post(`${urlAuth}/active`, {}, {
    'authorization': `Bearer ${token}`
  }).then(data => data);

  return Object.entries(res).length !== 0 ? res : undefined;
}

/* Modals */

export async function sendResetPassword(u) {
  const res = await http.post(`${urlAuth}/reset/send`, { "username": u })
    .then(data => data);

  return Object.entries(res).length !== 0 ? Object.values(res)[0] : false;
}

export async function userSignIn(u, p) {
  const res = await http.post(`${urlAuth}/login`, {
    "username": u,
    "password": p
  }).then(data => data);

  return Object.entries(res).length !== 0 ? res.token : '';
}