import AbstractModal from "./AbstractModal.js";
import { sendResetPassword } from "../../service/auth.js";

export default class extends AbstractModal {
  constructor() {
    super();

    this.init({
      modal: 'mod-forget',
      openBtn: 'forget-password',
      cancelBtn: 'mod-forget-cancelbtn',
      close: 'mod-forget-close',
      template: `
        <div id="mod-forget" class="mod">
          <form name="mod-forget-form" id="mod-forget-form" class="mod-content" method="post">

            <div class="mod-close-container">
              <span id="mod-forget-close" class="mod-common-close">&times;</span>
            </div>

            <div class="mod-title-container">
              <h1>Forget</h1>
            </div>

            <hr class="mod-separator">

            <div class="mod-common-main-container">
              <label for="mod-forget-username"><b>Username</b></label>
              <input id="mod-forget-username" type="text" placeholder="Enter Username" name="mod-forget-username" class="mod-common-input" required>

              <div class="mod-btn-container">
                <button type="submit" class="mod-acceptbtn">Send</button>
                <button type="button" id="mod-forget-cancelbtn" class="mod-cancelbtn">Cancel</button>
              </div>
            </div>

          </form>
        </div>
      `
    });
    this.open();
    this.close();
  }

  async sendReset() {
    this.modalForm = document.getElementById('mod-forget-form');
    this.modalForm.onsubmit = async (e) => {
      e.preventDefault();
      
      const u = document.forms["mod-forget-form"]["mod-forget-username"];
      if (this.validateForm(String(u.value))) {
        await sendResetPassword(String(u.value))
          .then(res => {
            if (res) {
              alert('Send! Check your email');
              u.value = "";
              this.hide();
            }
            else alert('Something wrong');
          })
      }
      else alert('Username wrong');
    }
  }

  validateForm(u) {
    const pRegex = /^[a-zA-Z0-9]{6,16}$/;

    return !(!u || !pRegex.test(u));
  }
}