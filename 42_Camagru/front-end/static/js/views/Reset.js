import AbstractView from "./AbstractView.js";
import { tokenVerify, resetPassword, isLogin } from "../service/auth.js";

export default class extends AbstractView {
  constructor() {
    super();

    this.setTitle("Reset");
  }

  async getHtml() {
    return await isLogin().then(async data => {
      if (!data) {
        return await tokenVerify().then(res => {
          return res
            ? `
              <h1 class="common-title" >Reset Password</h1>

              <hr class="common-separator">
        
              <form name="new-password-form" id="new-password-form" method="post">
                <label for="new-password">New password</label>
                <input type="password" placeholder="Enter new password" name="new-password" class="newpassword-input" maxlength="16" required>
        
                <button type="submit" class="newpasswprd">Reset</button>
              </form>
            `
            : '';
        })
      }
      else return '';
    })
    
  }

  async reset() {
    const query = location.search;
    const param = new URLSearchParams(query);
    const token = param.get('token');

    this.newPswForm = document.getElementById('new-password-form');
    this.newPswForm.onsubmit = async (e) => {
      e.preventDefault();

      const p = String(document.forms["new-password-form"]["new-password"].value);
      
      if (!token) {
        alert('Something wrong!');
        location = '/';
        return ;
      }
      if (this.validateForm(p)) {
        await resetPassword(token, p).then(res => {
          if (res) alert(`Password has been changed`);
          else alert(`Something wrong!`);

          location = '/';
        })
      }
    }
  }

  validateForm(p) {
    const pRegex = /^(?=.*\d)(?=.*[a-z])(?=.*[A-Z])[a-zA-Z0-9]{8,16}$/;

    if (!p || !pRegex.test(p)) {
      alert("- Password must contain a combination of uppercase\n- Lowercase letters and numbers\n- No special characters\n- Length between 8-16");
      return false;
    }
    return true;
  }
}