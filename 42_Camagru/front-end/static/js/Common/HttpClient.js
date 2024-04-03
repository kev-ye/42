export default class {
  constructor() {};

  async get (url, header) {
    const newH = {
      ...header
    };

    return await fetch(url, {
      method: 'get',
      headers: newH
    })
    .then(res => res.json())
    .catch(e => {
      return {};
    })
  }

  async post (url, body, header) {
    const newH = {
      ...header,
      "Content-Type": "application/json",
    };

    return await fetch(url, {
      method: 'post',
      body: JSON.stringify(body),
      headers: newH
    })
    .then(res => res.json())
    .catch(e => {
      return {};
    })
  }

  async put (url, body, header) {
    const newH = {
      ...header,
      "Content-Type": "application/json",
    };

    return await fetch(url, {
      method: 'put',
      body: JSON.stringify(body),
      headers: newH
    })
    .then(res => res.json())
    .catch(e => {
      return {};
    })
  }

  async delete (url, header) {
    const newH = {
      ...header,
      "Content-Type": "application/json",
    };

    return await fetch(url, {
      method: 'delete',
      headers: newH
    })
    .then(res => res.json())
    .catch(e => {
      return {};
    })
  }
}