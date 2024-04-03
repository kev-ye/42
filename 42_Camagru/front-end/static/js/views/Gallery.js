import AbstractView from "./AbstractView.js"
import { getAllImage, updateSocialInfo } from "../service/file.js";
import { userInfo } from "../service/user.js";
import ImageMod from "./modals/Image.js";
import SignIn from "./modals/SignIn.js";

export default class extends AbstractView {
  constructor() {
    super();

    this.setTitle('Gallery');
    this.fileArray = undefined;
    this.page = 0;
  }

  async getHtml() {
    return `
      <h1 class="common-title" >Gallery</h1>

      <hr class="common-separator">

      <div class="gallery-container">
        <ul id="gallery-collect"></ul>
        <div class="gallery-pagination-container">
          <button id="gallery-prev-btn" class="material-icons">arrow_back_ios</button>
          <button id="gallery-next-btn" class="material-icons">arrow_forward_ios</button>
        </div>
      </div>
    `;
  }

  async getAllCollect() {
    const res = await getAllImage().then(res => res);
    this.fileArray = Array.from(res.files).sort((file1, file2) => {
      if (file1.date > file2.date) return 1;
      else if (file1.date < file2.date) return -1;
      return 0;
    });

    await this.collectCanShow(this.fileArray);
    this.prevNextBtn(this.fileArray);
  }

  async collectCanShow() {
    const collect = document.getElementById('gallery-collect');
    const childNodes = Array.from(collect.childNodes);
  
    for (const childNode of childNodes)
      collect.removeChild(childNode);

    collect.innerHTML = '';

    const currentFirstElIdx = this.page === 0 ? 0 : this.page * 5;
    const nextFIrstrElIdx = this.page === 0 ? 5 : this.page * 5 + 5;

    const showCollectByPage = this.fileArray.filter(el => {
      if (this.fileArray.indexOf(el) >= currentFirstElIdx
        && this.fileArray.indexOf(el) < nextFIrstrElIdx)
        return el;
    });

    for (const file of showCollectByPage)
      await this.createImage(file);
  }

  async prevNextBtn() {
    const prevBtn = document.getElementById('gallery-prev-btn');
    const nextBtn = document.getElementById('gallery-next-btn');

    this.showPrevNextBtn(prevBtn, nextBtn, this.fileArray);

    prevBtn.onclick = async () => {
      if (this.page >= 0) this.page--;
      this.showPrevNextBtn(prevBtn, nextBtn, this.fileArray);
      await this.collectCanShow(this.fileArray);
    }

    nextBtn.onclick = async () => {
      this.page++;
      this.showPrevNextBtn(prevBtn, nextBtn, this.fileArray);
      await this.collectCanShow(this.fileArray);
    }
  }

  showPrevNextBtn(pB, nB) {
    if (this.page === 0) pB.style.visibility = 'hidden';
    else pB.style.visibility = 'visible';

    if (this.page * 5 + 5 >= this.fileArray.length) nB.style.visibility = 'hidden';
    else nB.style.visibility = 'visible'
  }

  async createImage(file) {
    const collect = document.getElementById('gallery-collect');

    const newList = document.createElement('li');
    const newImage = document.createElement('img');

    newList.classList.add('gallery-image-container')

    newImage.classList.add('gallery-image');
    newImage.id = file.id;
    newImage.src = file.data;

    collect.appendChild(newList);
    newList.appendChild(newImage);

    this.createSocialInfo(newList, file);
  }

  async createSocialInfo(parentNode, fileInfo) {
    const socialDiv = document.createElement('div');
    const socialLike = document.createElement('span');
    const socialComment = document.createElement('span');
    const socialLikeNumberDiv = document.createElement('div');
    const socialLikeNumber = document.createElement('span');

    socialDiv.id = `gallery-social-${fileInfo.id}`;
    socialDiv.classList.add('gallery-social-container');

    socialLike.classList.add('material-icons', 'gallery-social-content');
    socialComment.classList.add('material-icons', 'gallery-social-content');

    const user = await userInfo().then(data => data);
    if (user) socialLike.innerHTML = fileInfo.social.like.find(like => like === user.username) ? 'favorite' : 'favorite_border';
    else socialLike.innerHTML = 'favorite_border';
    socialComment.innerHTML = 'chat';

    socialLikeNumber.classList.add('gallery-social-likeNumber');
    socialLikeNumber.innerHTML = `${fileInfo.social.like.length} people like it!`;

    socialLike.id = `${fileInfo.id}-like`;
    socialComment.id = `${fileInfo.id}-comment`;

    parentNode.appendChild(socialDiv);
    socialDiv.appendChild(socialLike);
    socialDiv.appendChild(socialComment);
    
    socialDiv.appendChild(socialLikeNumberDiv)
    socialLikeNumberDiv.appendChild(socialLikeNumber);

    this.socialComment(fileInfo.id);
    this.socialClick(socialLike, socialComment, document.getElementById(`${fileInfo.id}-form`));
  }

  async socialClick(likeNode, commentNode, postNode) {
    likeNode.onclick = async (e) => {
      const token = localStorage.getItem('__token__');
      if (!token) {
        await this.callSignIn();
        return ;
      }
      const id = String(e.target.id).split('-')[0];

      const res = await updateSocialInfo({ like: true }, id).then(data => data);
      if (res) likeNode.innerHTML = likeNode.innerHTML === 'favorite' ? 'favorite_border' : 'favorite';
      else alert('Something wrong!');
    }

    commentNode.onclick = async (e) => {
      const imageMod = document.getElementById(`mod-image-${String(e.target.id).split('-')[0]}`);
      if (!imageMod) {
        const $imageMod = new ImageMod(String(e.target.id).split('-')[0]);
        await $imageMod.listImageComment();
        await $imageMod.comment();
      }
    }

    postNode.onsubmit = async (e) => {
      e.preventDefault();
      const token = localStorage.getItem('__token__');
      if (!token) {
        this.callSignIn();
        return ;
      }

      const id = String(e.target.id).split('-')[0];
      const commentForm = document.forms[`${e.target.id}`][`${e.target.id}-input`];
      const res = await updateSocialInfo({ comment: String(commentForm.value) }, id)
        .then(data => data);

      if (!res) alert('SomethingWrong');
      else commentForm.value = '';
    }
  }

  async socialComment(id) {
    const socialDiv = document.getElementById(`gallery-social-${id}`);
    const commentForm = document.createElement('form');
    const commentInput = document.createElement('input');
    const commentPost = document.createElement('button');

    commentForm.name = `${id}-form`;
    commentForm.id = `${id}-form`;
    commentForm.method = 'post';

    commentForm.classList.add('gallery-social-content-form');

    commentInput.placeholder = 'add a comment ...';
    commentInput.name = `${id}-form-input`;
    commentInput.maxLength = '100';
    commentInput.required = true;

    commentPost.type = 'submit';
    commentPost.innerHTML = 'Post';

    socialDiv.appendChild(commentForm);
    commentForm.appendChild(commentInput);
    commentForm.appendChild(commentPost);
  }


  /* utils */
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