import {ApiProfile} from "../global/global";

export const getCurrentUser = async () => {
	const token = localStorage.getItem('__access_token__')
	if (token === null) {
		document.location.href = '/login'
		return null
	}

	const url = `${ApiProfile}/profile`
	const headers = {authorization: `Bearer ${token}`}
	const res = await fetch(url, {
		method: 'get',
		headers
	})

	return await res.json()
}

export const setCurrentUser = async (f: Function) => {
	const token = localStorage.getItem('__access_token__')
	if (token !== null) {
		const url = `${ApiProfile}/profile`
		const headers = {authorization: `Bearer ${token}`}
		const res = await fetch(url, {
			method: 'get',
			headers
		})

		if (res.status !== 200) f(null)
		else f(await res.json())
	}
	else
		f(null)
}

export const updateUser = async (data: any) => {
	const token = localStorage.getItem('__access_token__')
	if (token === null) {
		document.location.href = '/login'
		return null
	}

	console.log(data)

	const url = `${ApiProfile}/profile`
	const headers = {
		authorization: `Bearer ${token}`,
		"Content-Type": "application/json",
	}
	const res = await fetch(url, {
		method: 'post',
		headers,
		body: JSON.stringify(data)
	})

	if (res.status !== 200) return null

	return await res.json()
}