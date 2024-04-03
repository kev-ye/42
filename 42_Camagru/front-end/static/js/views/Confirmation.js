import AbstractView from "./AbstractView.js";
import { isLogin, accountConfirmation } from "../service/auth.js";

export default class extends AbstractView {
  constructor() {
    super();

    this.setTitle("Confirmation");
  }

  async getHtml() {
    return await isLogin().then(res => {
      return Object.values(res)[0] === false
        ? `
          <h1>Confirmation</h1>

          <hr class="common-separator">

          <h2>Your account are not confirmed</h2>
          <button id="account-confirmation">Click it</button>
        `
        : '';
    })
  }

  async confirmation() {
    const token = localStorage.getItem('__token__');
    const confirmationBtn = document.getElementById('account-confirmation');

    confirmationBtn.onclick = async () => {
      if (!token) {
        alert('Something wrong!');
        location = '/';
        return ;
      }

      await accountConfirmation(String(token))
        .then(res => {
          if (res) alert(`A confirmation send to ${res.email}`);
          else alert('Something wrong!');

          location = '/';
        })
    }
  }
}