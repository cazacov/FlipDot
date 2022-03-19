<template>
  <h1>FlipDot-Board</h1>
  <board :board="board" />
</template>

<script>
import { defineComponent } from 'vue'
import { createBoard } from './board'
import Board from './components/Board.vue'


export default defineComponent({
  name: 'App',
  components: {
    Board
  },
  setup() {
    const board = createBoard(140, 19);
    return {
      board
    }
  }
})
</script>
