export default {
  items: [
    {
      name: 'Dashboard',
      url: '/admin/dashboard',
      icon: 'icon-speedometer',
      badge: {
        variant: 'info',
        text: 'NEW',
      },
    },
    {
      title: true,
      name: 'MonNaCorp',
      wrapper: {
        // optional wrapper object
        element: '', // required valid HTML5 element tag
        attributes: {}, // optional valid JS object with JS API naming ex: { className: "my-class", style: { fontFamily: "Verdana" }, id: "my-id"}
      },
      class: '', // optional class names space delimited list for title item ex: "text-center"
    },
    {
      name: 'Portfolio',
      url: '/admin/portfolio',
      icon: 'icon-layers',
      children: [
        {
          name: 'List',
          url: '/admin/portfolio',
          icon: 'icon-list',
        },
        {
          name: 'Add Portfolio',
          url: '/admin/portfolio-form',
          icon: 'icon-plus',
        },
      ],
    },
    {
      name: 'Tech News',
      url: '/admin/tech-news',
      icon: 'icon-layers',
      children: [
        {
          name: 'List',
          url: '/admin/tech-news',
          icon: 'icon-list',
        },
        {
          name: 'Add Tech News',
          url: '/admin/tech-news-form',
          icon: 'icon-plus',
        },
      ],
    },
    {
      name: 'Blog',
      url: '/admin/blog',
      icon: 'icon-layers',
      children: [
        {
          name: 'List',
          url: '/admin/blog',
          icon: 'icon-list',
        },
        {
          name: 'Add blog',
          url: '/admin/blog-form',
          icon: 'icon-plus',
        },
      ],
    },
    {
      divider: true,
    },
  ],
};
