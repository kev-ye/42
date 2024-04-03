import AbstractModal from "./AbstractModal.js";
import { createNewUser } from "../../service/user.js";

export default class extends AbstractModal {
  constructor() {
    super();

    this.init({
      modal: 'mod-signUp',
      openBtn: 'sign-up',
      cancelBtn: 'mod-signUp-cancelbtn',
      close: 'mod-signUp-close',
      template: `
      <div id="mod-signUp" class="mod">
        <form name="mod-signUp-form" id="mod-signUp-form" class="mod-content" method="post">

          <div class="mod-close-container">
            <span id="mod-signUp-close" class="mod-common-close">&times;</span>
          </div>

          <div class="mod-title-container">
            <h1>Sign Up</h1>
          </div>

          <hr class="mod-separator">

          <div class="mod-common-main-container">
            <label for="mod-signUp-username"><b>Username</b></label>
            <input id="mod-signUpUsername" type="text" placeholder="Enter Username" name="mod-signUp-username" class="mod-common-input" maxlength="16" required>

            <label for="mod-signUp-psw"><b>Password</b></label>
            <input id="mod-signUpPassword" type="password" placeholder="Enter Password" name="mod-signUp-psw" class="mod-common-input" maxlength="16" required>

            <label for="mod-signUp-email"><b>Email</b></label>
            <input id="mod-signUpemail" type="text" placeholder="Enter email" name="mod-signUp-email" class="mod-common-input" maxlength="100" required>

            <div class="mod-btn-container">
              <button type="submit" class="mod-acceptbtn">Sign up</button>
              <button type="button" id="mod-signUp-cancelbtn" class="mod-cancelbtn">Cancel</button>
            </div>
          </div>
        </form> 
      </div>
      `
    });
    this.open();
    this.close();
  }

  async accept() {
    this.modalForm = document.getElementById('mod-signUp-form');
    this.modalForm.onsubmit = async (e) => {
      e.preventDefault();

      const u = document.forms["mod-signUp-form"]["mod-signUp-username"];
      const p = document.forms["mod-signUp-form"]["mod-signUp-psw"];
      const m = document.forms["mod-signUp-form"]["mod-signUp-email"];

      if (this.validateForm(String(u.value), String(p.value), String(m.value))) {
        await createNewUser(
          String(u.value),
          String(p.value),
          String(m.value)
        ).then(created => {
          if (created) {
            alert(`User ${String(u.value)} created.\nA confirmation send to ${String(m.value)}`);
            this.cleanInput(u, p, m);
            this.hide();
          }
          else alert(`User ${String(u.value)} already exist!`);
        });
      }
    }
  }

  validateForm(u, p, m) {
    const uRegex = /^[a-zA-Z0-9]{6,16}$/;
    const pRegex = /^(?=.*\d)(?=.*[a-z])(?=.*[A-Z])[a-zA-Z0-9]{8,16}$/;
    const mRegex = /^[a-zA-Z0-9._-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,4}$/;

    if (!u || !uRegex.test(u)) {
      alert("- Username must contain letters or numbers\n- Length between 6-16");
      return false;
    }

    if (!p || !pRegex.test(p)) {
      alert("- Password must contain a combination of uppercase and lowercase letters and numbers\n- No special characters\n- Length between 8-16");
      return false;
    }

    if (!m || !mRegex.test(m)) {
      alert("Email format isn't correct");
      return false;
    }

    return true;
  }

  cleanInput(u, p, m) {
    u.value = "";
    p.value = "";
    m.value = "";
  }
}