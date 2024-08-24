#include <cpu.h>
#include <bus.h> 
#include <emu.h>
cpu_context context = {0};

void cpu_init()
{
    printf("Initiating CPU. \n ");
}

static void fetch_instruction() {
  context.current_opcode = bus_read(context.registers.pc++);
  context.current_instruction = instruction_by_opcode(context.current_opcode);

  if(context.current_instruction == NULL){
    printf("Unknown Instruction! %d \n", context.current_instruction->mode);
    exit(-7);
  }
}

static void fetch_data() {
  context.memory_destination = 0;
  context.destination_is_memory = false;

  switch(context.current_instruction->mode){
    case AM_IMP: return;

    case AM_R:
      context.fetched_data = cpu_read_register(context.current_instruction->register_1);

    case AM_D16:
      u16 low = bus_read(context.registers.pc +1 );
      emulator_cycles(1);
      u16 high = bus_read(context.registers.pc + 1 );
      emulator_cycles(1);

    default:
      printf(" Unknown address mode! %d \n", context.current_instruction->mode);
        exit(-7);
  }
}

static void execute(){
  printf("Not executing yet... \n");
}

void emulator_cycles(int cpu_cycles){

}

u16 cpu_read_register(register_type register){
  return 0;
}


bool cpu_step()
{
  if(!context.halted){
    fetch_instruction();
    fetch_data();
    execute();
  }
  printf("Cpu not yet implemented.\n");
    return false;
}
