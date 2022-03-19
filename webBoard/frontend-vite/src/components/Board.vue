<template>
    <h2> The Board</h2>
    <table>
        <tr v-for="(row,y) in board.field" :key="y">
            <lot v-for="(cell,x) in row" :key="x" :cell="cell"/>
        </tr>
    </table>
</template>

<script lang="ts">
import { defineComponent } from 'vue'
import Lot from './Lot.vue'
export default defineComponent({
    components: {
        Lot
    },
    props: ['board']
})
</script>

<style scoped>
    table {
        border: 1px solid gray;
    }
    
</style>