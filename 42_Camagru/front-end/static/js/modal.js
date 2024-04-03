import SignIn from "./views/modals/SignIn.js"
import SignUp from "./views/modals/SignUp.js";

export const signIn = async () => {
  const signInMod = document.getElementById('mod-signIn');
  if (!signInMod) {
    const $signIn = new SignIn();
    await $signIn.accept();
    await $signIn.forgetPassword();
  }
}

export const signUp = async () => {
  const signUpMod = document.getElementById('mod-signUp');
  if (!signUpMod) {
    const $signUp = new SignUp();
    await $signUp.accept();
  }
}

const modDefaultClose = (id) => {
  const toclose = document.getElementById(id);

  if (['mod-signIn', 'mod-signUp', 'mod-forget'].find(el => el === id)) {
    toclose.style.display = 'none';
  }

  const imgModId = String(id).split('-');
  if (imgModId.length === 3 && `${imgModId[0]}-${imgModId[1]}` === 'mod-image') {
    const toCloseImgMod = document.getElementById(id);
    toCloseImgMod.style.display = 'none';
  }
}

document.addEventListener("DOMContentLoaded", () => {
  document.body.addEventListener("click", async e => {
    if (e.target) {
      switch(e.target.id) {
        case 'sign-in':
          await signIn();
          break ;
        case 'sign-up':
          await signUp();
          break ;
        default:
          modDefaultClose(e.target.id);
          break ;
      }
    }
  })
})