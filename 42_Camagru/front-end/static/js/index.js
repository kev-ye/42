import Gallery from "./views/Gallery.js";
import User from "./views/User.js";
import Nav from "./views/Nav.js";
import Reset from "./views/Reset.js";
import Confirmation from "./views/Confirmation.js";
import Montage from "./views/montage.js";
import { isLogin } from "./service/auth.js";

const navigateTo = url => {
  history.pushState(null, null, url);
  router().then();
}

const router = async () => {
  const routes = [
    { path: "/", view: Gallery },
    { path: "/user", view: User },
    { path: "/montage", view: Montage },
    { path: "/reset", view: Reset },
    { path: "/confirmation", view: Confirmation }
  ];

  const potentialMatches = routes.map(route => {
    return {
      route: route,
      isMatch: location.pathname === route.path
    };
  });

  let match = potentialMatches.find(potentialMatch => potentialMatch.isMatch);

  if (!match) {
    match = {
      route: routes[0],
      isMatch: true
    };
  }

  const nav = new Nav();
  const view = new match.route.view();
  const noNavPath = ['/reset', '/confirmation'];

  let pageAction = true;

  if (!noNavPath.find(path => path === location.pathname)) {
    document.getElementById('nav').innerHTML = await nav.getHtml().then(res => res);
  }
  document.getElementById('app').innerHTML = await view.getHtml().then(async res => {
    if (res) return res;
    else {          pageAction = false;
      await isLogin().then(res => {
        pageAction = false;
        if (res) {
          if (['/reset', '/confirmation'].find(el => el === location.pathname)) {
            alert('You don\'t have permission to this page');
            location = '/';
          }
          else if (['/user', '/montage'].find(el => el === location.pathname)) {
            alert('Your account isn\'t confirmed!');
            location = '/confirmation'
          }
          else {
            location = '/';
          }
        }
        else {
          alert('You don\'t have permission to this page');
          location = '/';
        }
      });
    }
  });

  switch (pageAction && location.pathname) {
    case '/':
      await view.getAllCollect().then();
      break ;
    case '/user':
      await view.globalUserInfoEditControl().then();
      await view.userInfoEdit().then();
      await view.notify().then();
      break ;
    case '/reset':
      await view.reset().then();
      break ;
    case '/confirmation':
      await view.confirmation().then();
      break ;
    case '/montage':
      await view.openCamera();
      await view.loadCollectImage();
      await view.uploadImageFromFile();
      break ;
    default :
      break ;
  }
}

const exit = async () => {
  localStorage.removeItem('__token__');
  location = '/';
}

// Event

window.addEventListener("popstate", router);

document.addEventListener("DOMContentLoaded", () => {
  document.body.addEventListener("click", e => {
    if (e.target) {
      if (e.target.matches("[data-link]")) {
        e.preventDefault();
        navigateTo(e.target.href);
      }

      switch(e.target.id) {
        case 'user-exit':
          exit();
          break ;
        default:
          break ;
      }
    }
  });
  router().then();
});