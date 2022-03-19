<template >
    <td></td>
</template>

<script lang="ts">
import { defineComponent} from 'vue'
export default defineComponent({
    props:['cell'],
    setup(props) {
        const cell = props.cell
    }
})
</script>
<style scoped> 
    td {
        border: 1px solid lightgrey;
        width: 10px;
        height: 10px;
        padding: 0;
    }
</style>