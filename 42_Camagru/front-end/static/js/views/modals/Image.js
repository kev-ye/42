import { getImageWithoutAuth, updateSocialInfo } from "../../service/file.js";
import AbstractModal from "./AbstractModal.js";
import SignIn from "./SignIn.js";

export default class extends AbstractModal {
  constructor(id) {
    super();

    this.init({
      modal: `mod-image-${id}`,
      openBtn: `${id}-comment`,
      close: `mod-image-${id}-close`,
      template: `
        <div id="mod-image-${id}" class="mod">
          <div class="mod-content-image">

            <div class="mod-image-info-container">
              <div class="mod-close-container">
                <span id="mod-image-${id}-close" class="mod-common-close">&times;</span>
              </div>

              <div class="mod-title-container">
                <h1>Picture: ${id}</h1>
              </div>

              <hr class="mod-separator">
            </div>
            
            <div class="mod-image-social-content">
              <div class="mod-image-container">
                <img src="${this.getImageSrc(id)}" class="mod-image-content">
              </div>

              <div class="mod-image-comment-container">
                <ul id="mod-image-${id}-comment-list">
                </ul>
              <div>

              <form name="mod-image-${id}-form" id="mod-image-${id}-form" class="mod-image-comment-input-container" post>
                <input name="mod-image-${id}-form-input" placeholder="add a comment ..." maxlength="100" required>
                <button type="submit">Post</button>
              </form>
            </div>

          </div>
        </div>
      `
    });
    this.open();
    this.close();
    this.id = id;
    this.timerId = undefined;
  }

  getImageSrc(id) {
    return document.getElementById(id).src;
  }

  async listImageComment() {
    const imageInfo = await getImageWithoutAuth(this.id).then(data => data);
    const commentArray = Array.from(imageInfo.social.comment)
      .sort((c1, c2) => {
        if (c1.date > c2.date) return 1;
        else if (c1.date < c2.date) return -1;
        return 0;
      });
    const list = document.getElementById(`mod-image-${this.id}-comment-list`)

    for (const comment of commentArray) {
      this.createNewComment(list, comment.user, comment.comment);
    }
  }

  async refreshListComment() {
    const imageInfo = await getImageWithoutAuth(this.id).then(data => data);
    const commentArray = Array.from(imageInfo.social.comment)
      .sort((c1, c2) => {
        if (c1.date > c2.date) return 1;
        else if (c1.date < c2.date) return -1;
        return 0;
      });
    const list = document.getElementById(`mod-image-${this.id}-comment-list`)

    if (list.childNodes.length - 1 < commentArray.length) {
      for (let i = list.childNodes.length - 1; i < commentArray.length; i++) {
        this.createNewComment(list, commentArray[i].user, commentArray[i].comment);
      }
    }
  } 

  createNewComment(parent, commentUser, comment) {
    const newLi = document.createElement('li');
    const user = document.createElement('b');
    const message = document.createElement('span');

    user.innerText = `${commentUser}: `;
    message.innerText = comment;

    parent.appendChild(newLi);
    newLi.appendChild(user);
    newLi.appendChild(message)
  }

  async comment() {
    const commentInput = document.getElementById(`mod-image-${this.id}-form`);

    commentInput.onsubmit = async (e) => {
      e.preventDefault();
      const token = localStorage.getItem('__token__');
      if (!token) {
        await this.callSignIn();
        return ;
      }
      const commentForm = document.forms[`mod-image-${this.id}-form`][`mod-image-${this.id}-form-input`];
      const res = await updateSocialInfo({ comment: String(commentForm.value) }, this.id)
        .then(data => data);

      if (!res) alert('SomethingWrong');
      else {
        await this.refreshListComment();
        commentForm.value = '';
      }
    }
  }

  addTimer() {
    this.timerId = setInterval(async () => {
      await this.refreshListComment().then();
    }, 3 * 1000);
  }

  deleteTimer() {
    clearInterval(this.timerId);
    this.timerId = null;
  }

  open() {
    addEventListener("click", e => {
      if (e.target && e.target.id === this.openBtn.id) {
        this.modal.style.display = "block";

        if (!this.timerId) this.addTimer();
      }
    });
  }

  close() {
    addEventListener("click", e => {
      if (e.target && e.target.id === this.cancelSpan.id) {
        this.modal.style.display = "none";

        this.deleteTimer()
      }
    });
  }

  async callSignIn() {
    const signInMod = document.getElementById('mod-signIn');
    if (!signInMod) {
      const $signIn = new SignIn();
      await $signIn.accept();
      await $signIn.forgetPassword();
    }
    else {
      signInMod.style.display = 'block';
    }
  }
}