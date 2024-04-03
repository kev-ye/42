import AbstractModal from "./AbstractModal.js"
import Forget from "./Forget.js"
import { userSignIn } from "../../service/auth.js";

export default class extends AbstractModal {
   constructor() {
    super();

    this.init({
      modal: 'mod-signIn',
      openBtn: 'sign-in',
      cancelBtn: 'mod-signIn-cancelbtn',
      close: 'mod-signIn-close',
      template: `
        <div id="mod-signIn" class="mod">
          <form name="mod-signIn-form" id="mod-signIn-form" class="mod-content" method="post">

            <div class="mod-close-container">
              <span id="mod-signIn-close" class="mod-common-close">&times;</span>
            </div>

            <div class="mod-title-container">
              <h1>Sign In</h1>
            </div>

            <hr class="mod-separator">

            <div class="mod-common-main-container">
              <label for="mod-signIn-username"><b>Username</b></label>
              <input type="text" placeholder="Enter Username" name="mod-signIn-username" class="mod-common-input" maxlength="16" required>

              <label for="mod-signIn-psw"><b>Password</b></label>
              <input type="password" placeholder="Enter Password" name="mod-signIn-psw" class="mod-common-input" maxlength="16" required>

              <div class="mod-btn-container">
                <button type="submit" class="mod-acceptbtn">Sign in</button>
                <button type="button" id="mod-signIn-cancelbtn" class="mod-cancelbtn">Cancel</button>
              </div>
            </div>

            <div class="mod-common-main-container">
              <span class="mod-signIn-psw">Forgot <a id="forget-password" href="">password?</a></span>
            </div>
          </form>
        </div>
      `
    });
    this.open();
    this.close();
  }

  async accept() {
    this.modalForm = document.getElementById('mod-signIn-form');
    this.modalForm.onsubmit = async (e) => {
      e.preventDefault();

      const u = String(document.forms["mod-signIn-form"]["mod-signIn-username"].value);
      const p = String(document.forms["mod-signIn-form"]["mod-signIn-psw"].value);

      if (this.validateForm(u, p)) {
        await userSignIn(u, p).then(token => {
          if (token) {
            localStorage.setItem('__token__', token);
            location.reload();
          }
          else alert('Username or password wrong');
        })
      }
      else
        alert('Username or password wrong');
    }
  }

  async forgetPassword() {
    this.forget = document.getElementById('forget-password');
    const forgetMod = document.getElementById('mod-forget');
  
    if (!forgetMod) {
      this.$forgetMod = new Forget();
      await this.$forgetMod.sendReset();

      const fm = document.getElementById('mod-forget');
      fm.style.display = 'none';
    }
    this.forget.onclick = async (e) => {
      e.preventDefault();
      this.modal.style.display = 'none';

      const fm = document.getElementById('mod-forget');
      fm.style.display = 'block';
    }
  }

  validateForm(u, p) {
    const uRegex = /^[a-zA-Z0-9]{6,16}$/;
    const pRegex = /^(?=.*\d)(?=.*[a-z])(?=.*[A-Z])[a-zA-Z0-9]{8,16}$/;

    if (!u || !uRegex.test(u)) return false;
    if (!p || !pRegex.test(p)) return false;

    return true;
  }
}