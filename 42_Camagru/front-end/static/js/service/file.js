import HttpClient from "../Common/HttpClient.js";

const http = new HttpClient();
const urlUser = '/api/file';

export async function uploadImage(data) {
	const token = localStorage.getItem('__token__');
	if (!token)
		return undefined;

	const res = await http.post(`${urlUser}/upload`, { data: data }, {
		'authorization': `Bearer ${token}`
	}).then(data => data);

	return Object.entries(res).length === 0 ? undefined : res;
}

export async function getAllImage() {
	const res = await http.get(`${urlUser}`).then(data => data);

	return Object.entries(res).length === 0 ? undefined : res;
}

export async function getImage(id) {
	const token = localStorage.getItem('__token__');
	if (!token)
		return undefined;

	const res = await http.get(`${urlUser}/${id}`, {
		'authorization': `Bearer ${token}`
	}).then(data => data);

	return Object.entries(res).length === 0 ? undefined : res;
}

export async function getImageWithoutAuth(id) {
	const res = await http.get(`${urlUser}/info/${id}`).then(data => data);

	return Object.entries(res).length === 0 ? undefined : res;
}

export async function removeImage(id) {
	const token = localStorage.getItem('__token__');
	if (!token)
		return undefined;

	const res = await http.delete(`${urlUser}/${id}`, {
		'authorization': `Bearer ${token}`
	}).then(data => data);

	return Object.entries(res).length === 0 ? undefined : res;
}

export async function updateSocialInfo(info, id) {
	const token = localStorage.getItem('__token__');
	if (!token)
		return undefined;

	const res = await http.put(`${urlUser}/${id}`, { ...info }, {
		'authorization': `Bearer ${token}`
	}).then(data => data);

	return Object.entries(res).length === 0 ? false : true;
}