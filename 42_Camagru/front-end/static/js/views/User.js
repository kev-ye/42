import AbstractView from "./AbstractView.js";
import { haveAccess } from "../service/auth.js";
import { userInfo, updateUser } from "../service/user.js";

export default class extends AbstractView {
  constructor() {
    super();

    this.setTitle("User");
  }

  async getHtml() {
    return await haveAccess().then(async res => {
      if (res) {
        return await userInfo().then(res => {
          if (res) {
            return `
              <h1 class="common-title" >User</h1>

              <hr class="common-separator">
    
              <div class="user-edit-container">
                <div class="user-edit-content">
                  <ul id="user-edit-control">
                    <li id="user-username-edit">
                      ${this.originalTemplate({
                        info: "Username",
                        content: res.username,
                        id: "user-username-edit-btn"
                      })}
                    </li>
                    <li id="user-email-edit">
                      ${this.originalTemplate({
                        info: "Email",
                        content: res.email,
                        id: "user-email-edit-btn"
                      })}
                    </li>
                    <li id="user-password-edit">
                      <button id="user-password-edit-btn">Change password</button>
                    </li>
                  </ul>

                  <span class="user-notify">Notify: </span>
                  <label class="user-notify-switch">
                    <input type="checkbox" id="user-notify-input" class="user-notify-input">
                    <span class="user-notify-slider user-notify-round"></span>
                  </label>
                </div>
              </div>
            `;
          }
          else return '';
        });
      } else return '';
    });
  }

/* notify */
  async notify() {
    const userNotify = document.getElementById('user-notify-input');
    const user = await userInfo().then(data => data);

    userNotify.checked = user && user.notify === true ? 'checked' : '';

    userNotify.onclick = async () => {
      const user = await userInfo().then(data => data);
      await updateUser(
        undefined,
        undefined,
        undefined,
        undefined,
        user.notify === true ? false : true
      ).then(res => {
        if (!res) alert('Something wrong');
      });
    }
  }

/* click event control */

  async globalUserInfoEditControl() {
    const editControl = document.getElementById('user-edit-control');

    editControl.addEventListener("click", async e => {
      if (e.target) {
        switch (e.target.id) {
          case 'user-username-accept-btn':
            await this.accept('username').then();
            break ;
          case 'user-email-accept-btn':
            await this.accept('email').then();
            break ;
          case 'user-password-accept-btn':
            await this.accept('password').then();
            break ;
          case 'user-username-cancel-btn':
            await this.cancel('username').then();
            break ;
          case 'user-email-cancel-btn':
            await this.cancel('email').then();
            break ;
          case 'user-password-cancel-btn':
            await this.cancel('password').then();
            break ;
          default:
            break ;
        }
      }
    })
  }

  async userInfoEdit() {
    const uEdit = document.getElementById('user-username-edit');
    const uEditBtn = document.getElementById('user-username-edit-btn');

    if (uEditBtn) {
      uEditBtn.onclick = async () => {
        uEdit.innerHTML = this.editTemplate({
          info: "Username",
          inputId: "user-username-input",
          value: await userInfo().then(res => res.username),
          acceptBtnId: "user-username-accept-btn",
          cancelBtnId: "user-username-cancel-btn"
        })
      }
    }

    const mEdit = document.getElementById('user-email-edit');
    const mEditBtn = document.getElementById('user-email-edit-btn');

    if (mEditBtn) {
      mEditBtn.onclick = async () => {
        mEdit.innerHTML = this.editTemplate({
          info: "Email",
          inputId: "user-email-input",
          value: await userInfo().then(res => res.email),
          acceptBtnId: "user-email-accept-btn",
          cancelBtnId: "user-email-cancel-btn"
        })
      }
    }

    const pEdit = document.getElementById('user-password-edit');
    const pEditBtn = document.getElementById('user-password-edit-btn');
    if (pEditBtn) {
      pEditBtn.onclick = () => {
        pEdit.innerHTML = this.pswEditTemplate();
      }
    }
  }

/* accept & cancel request */

  async accept(info = '') {
    if (['username', 'email'].find(el => el === info)) {
      const value = document.getElementById(`user-${info}-input`).value;

      if (info === 'username') {
        if (!this.validateFormU(String(value)) || String(value).length > 16) {
          alert('Username format wrong!');
          return ;
        }
      }

      if (info === 'email') {
        if (!this.validateFormM(String(value)) || String(value).length > 50) {
          alert('Email format wrong!');
          return ;
        }
      }

      await updateUser(
        info === 'username'? value : undefined,
        undefined,
        undefined,
        info === 'username'? undefined : value,
        undefined).then(async res => {
          if (!res) alert('Username already exist!');
          else {
            localStorage.setItem('__token__', res.token);
            await this.cancel(info);
          }
        });
    }
    else {
      const oldValue = document.getElementById('user-old-password-input').value;
      const newValue = document.getElementById('user-new-password-input').value;

      if (!this.validateFormP(String(oldValue) || !this.validateFormP(String(newValue)))) {
        alert('Old/New password format wrong!');
        return ;
      }

      await updateUser(
        undefined,
        newValue,
        oldValue,
        undefined,
        undefined).then(async res => {
          if (!res) alert('Old password wrong!');
          else {
            await this.cancel(info);
          }
        });
    }
  }

  async cancel(info = '') {
    if (['username', 'email'].find(el => el === info)) {
      const infoEdit = document.getElementById(`user-${info}-edit`);
      infoEdit.innerHTML = this.originalTemplate({
        info: info === 'username' ? "Username" : "Email",
        content: await userInfo().then(u => info === 'username' ? u.username : u.email),
        id: `user-${info}-edit-btn`
      });
    }
    else {
      const infoEdit = document.getElementById('user-password-edit');
      infoEdit.innerHTML = this.pswOriginalTemplate();
    }
    await this.userInfoEdit();
  }

/* utils template */

  originalTemplate (info = {}) {
    return `<b>${info.info}: </b>${info.content}<span id="${info.id}" class="material-icons">edit</span>`;
  }

  editTemplate (edit = {}) {
    return `
      <b>${edit.info}: </b>
      <input id="${edit.inputId}" class="user-edit-${String(edit.info).toLowerCase()}"  type="text" value="${edit.value}" maxlength="${edit.info === 'Username' ? 16 : 50}" required>
      <button id="${edit.acceptBtnId}" class="user-edit-btn">
        Update
      </button>
      <button id="${edit.cancelBtnId}" class="user-edit-btn">
        Cancel
      </button>
      `;
  }

  pswOriginalTemplate () {
    return '<button id="user-password-edit-btn">Change password</button>';
  }

  pswEditTemplate () {
    return `  
      <div>
        <b>Old password: </b><input id="user-old-password-input" type="password" placeholder="Enter your old password" maxlength="16" required>
      </div>
      <div>
        <b>New password: </b><input id="user-new-password-input" type="password" placeholder="Enter your new password" maxlength="16" required>
      </div>
      <div>
        <button id="user-password-accept-btn">Update</button>
        <button id="user-password-cancel-btn">Cancel</button>
      </div>
    `;
  }

  validateFormU(u) {
    const uRegex = /^[a-zA-Z0-9]{6,16}$/;
  
    if (!u || !uRegex.test(u)) return false;

    return true;
  }

  validateFormP(p) {
    const pRegex = /^(?=.*\d)(?=.*[a-z])(?=.*[A-Z])[a-zA-Z0-9]{8,16}$/;
  
    if (!p || !pRegex.test(p)) return false;

    return true;
  }

  validateFormM(m) {
    const mRegex = /^[a-zA-Z0-9._-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,4}$/;

    if (!m || !mRegex.test(m)) return false;

    return true;
  }
}