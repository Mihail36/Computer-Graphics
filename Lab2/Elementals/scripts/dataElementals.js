const dataElementals = [{
        tagName: 'Вода',
        name: 'water',
        src: 'images/water.svg',
        variantsCombinations: []
    },

    {
        tagName: 'Огонь',
        name: 'fire',
        src: 'images/fire.svg',
        variantsCombinations: []
    },

    {
        tagName: 'Земля',
        name: 'ground',
        src: 'images/ground.svg',
        variantsCombinations: []
    },

    {
        tagName: 'Воздух',
        name: 'air',
        src: 'images/air.svg',
        variantsCombinations: []
    },

    {
        tagName: 'Пыль',
        name: 'dust',
        src: 'images/dust.svg',
        variantsCombinations: ['ground+air', 'air+ground']
    },

    {
        tagName: 'Камень',
        name: 'stone',
        src: 'images/stone.svg',
        variantsCombinations: ['lava+water', 'water+lava', 'dust+dust']
    },

    {
        tagName: 'Гора',
        name: 'mountain',
        src: 'images/mountain.svg',
        variantsCombinations: ['stone+stone']
    },

    {
        tagName: 'Металл',
        name: 'metal',
        src: 'images/metal.svg',
        variantsCombinations: ['stone+fire', 'fire+stone']
    },

    {
        tagName: 'Вулкан',
        name: 'volcano',
        src: 'images/volcano.svg',
        variantsCombinations: ['mountain+fire', 'fire+mountain']
    },

    {
        tagName: 'Лава',
        name: 'lava',
        src: 'images/lava.svg',
        variantsCombinations: ['volcano+water', 'water+volcano']
    },

    {
        tagName: 'Песок',
        name: 'sand',
        src: 'images/sand.svg',
        variantsCombinations: ['air+stone', 'stone+air']
    },

    {
        tagName: 'Пар',
        name: 'steam',
        src: 'images/steam.svg',
        variantsCombinations: ['fire+water', 'water+fire']
    },

    {
        tagName: 'Облако',
        name: 'cloud',
        src: 'images/cloud.svg',
        variantsCombinations: ['steam+steam']
    },

    {
        tagName: 'Туча',
        name: 'dark_cloud',
        src: 'images/dark_cloud.svg',
        variantsCombinations: ['cloud+cloud']
    },

    {
        tagName: 'Молния',
        name: 'lightning',
        src: 'images/lightning.svg',
        variantsCombinations: ['dark_cloud+dark_cloud']
    },

    {
        tagName: 'Электричество',
        name: 'electricity',
        src: 'images/electricity.svg',
        variantsCombinations: ['lightning+metal', 'metal+lightning']
    },

    {
        tagName: 'Паровой двигатель',
        name: 'steam_engine',
        src: 'images/steam_engine.svg',
        variantsCombinations: ['steam+metal', 'metal+steam']
    },

    {
        tagName: 'Паровоз',
        name: 'steam_train',
        src: 'images/steam_train.svg',
        variantsCombinations: ['steam_engine+ground', 'ground+steam_engine']
    },

    {
        tagName: 'Пароход',
        name: 'steam_boat',
        src: 'images/steam_boat.svg',
        variantsCombinations: ['steam_engine+water', 'water+steam_engine']
    },

    {
        tagName: 'Остров',
        name: 'island',
        src: 'images/island.svg',
        variantsCombinations: ['ground+ground']
    },

    {
        tagName: 'Континент',
        name: 'continent',
        src: 'images/continent.svg',
        variantsCombinations: ['island+island']
    },

    {
        tagName: 'Планета',
        name: 'planet',
        src: 'images/planet.svg',
        variantsCombinations: ['continent+continent']
    },

    {
        tagName: 'Галактика',
        name: 'galaxy',
        src: 'images/galaxy.svg',
        variantsCombinations: ['planet+planet']
    },

    {
        tagName: 'Вселенная',
        name: 'universe',
        src: 'images/universe.svg',
        variantsCombinations: ['galaxy+galaxy']
    }
]

export { dataElementals };